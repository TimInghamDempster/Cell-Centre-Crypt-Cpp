
/*************************************************************************************

The Crypt struct does the majority of the work of the simulation.  It owns a grid
which contains the data for the cells and the update rules for anything to do with
the biological rules, in particular contains all the code for cell cycle update,
membrane attachment, anoikis and simulation boundaries.

*************************************************************************************/
struct  Crypt
{

	int m_numRows;
	int m_numColumns;
	
	const double m_secondsPerTimestep;
	
	const double m_cryptRadius;
	const double m_flutingRadius;

	const double m_compressionFactor;
	const double m_cellSize;
	const double m_cellsPerSectionInNiche;
    const double m_cellsPerSectionInTop;
    const double m_numVerticalCells;
	const double m_cryptHeight;
	
	const double m_basicG0ProliferationBoundary;
	const double m_basicG0StemBoundary;
	
	const double m_averageGrowthTimesteps;
	const double m_requiredG0TimestepsStem;
	const double m_requiredG0TimestepsProliferation;
	const double m_MPhaseTimesteps;

	const double m_colonBoundaryRepulsionFactor;
	const double m_offMembraneRestorationFactor;
	const double m_stromalRestorationFactor;
	const double m_membraneSeparationToTriggerAnoikis;

	Vector2D m_colonBoundary;

	const Vector3D m_pos;

	//std::vector<Vector3D> deadcells;

	int m_numBirthEvents;
	int m_numAnoikisEvents;

	int m_cellularity;

	int m_anoikisHeights[100];

	CylindricalGrid m_grid;
	NormalDistributionRNG* m_normalRNG;

	std::vector<int> m_migrationTimes;

	Crypt(int numRows, int numColumns, double averageGrowthTimeSeconds, double attachmentForce, Vector2D boundary, NormalDistributionRNG* normalRNG, Vector3D position, int cryptId) : 
		m_numRows(numRows),
		m_numColumns(numColumns),
		m_secondsPerTimestep(30.0f),
		m_cryptRadius(500.0f),
		m_flutingRadius(500.0f),
		m_compressionFactor(1.75f),
		m_cellSize(m_cryptRadius * 2.0f * (double)PI / (numColumns * 2.0f)),
		m_cellsPerSectionInNiche(m_cryptRadius * 2.0f * PI / 4.0f /(m_cellSize * 2.0f)), // Quarter circumference (2 * Pi * R / 4) / cell size (2 * r)
		m_cellsPerSectionInTop(m_flutingRadius * 2.0f * PI / 4.0f / (m_cellSize * 2.0f)), // Quarter circumference (2 * Pi * R / 4) / cell size (2 * r)
		m_numVerticalCells(numRows - m_cellsPerSectionInNiche - m_cellsPerSectionInTop), // Work out how many cells in the vertical section of the crypt
		m_cryptHeight((m_cellSize * 2.0f * m_numVerticalCells + m_cryptRadius + m_flutingRadius) / m_compressionFactor),
		m_basicG0ProliferationBoundary(m_cryptHeight * -0.7f),
		m_basicG0StemBoundary(m_cryptHeight * -0.95f),
		m_averageGrowthTimesteps(averageGrowthTimeSeconds / m_secondsPerTimestep),
		m_requiredG0TimestepsStem(m_averageGrowthTimesteps * 9.0f),
		m_requiredG0TimestepsProliferation(100.0f),
		m_MPhaseTimesteps(1238.4f / m_secondsPerTimestep),
		m_colonBoundaryRepulsionFactor(0.3f),
		m_offMembraneRestorationFactor(attachmentForce),
		m_stromalRestorationFactor(0.3f),

		m_membraneSeparationToTriggerAnoikis(m_cellSize * 1.0),

		m_colonBoundary(boundary),
		m_normalRNG(normalRNG),
		m_numBirthEvents(0),
		m_numAnoikisEvents(0),
		m_cellularity(0),
		m_grid(numRows / 2, numColumns / 2, numRows * 2, 4, m_cryptHeight, 1238.4f / m_secondsPerTimestep, position),
		m_pos(position)
	{
		CellReference ref;
		Vector3D pos(0.0f, m_cryptHeight * -0.999f, 0.0f);
		CellBox* box = m_grid.FindBox(pos);
		//box->AddCell(pos, pos, 0.0f, m_cellSize, 0, (int)m_normalRNG(m_random_generator), ref, CellCycleStages::G0);
		PopulateCrypt(cryptId);

		for(int i = 0; i < 100; i++)
		{
			m_anoikisHeights[i] = 0;
		}
	}

	void PopulateCrypt(int cryptId)
		{
			for(int hIndex = 1; hIndex < m_numRows / m_compressionFactor - 2; hIndex++)
			{
				double height = ( m_cryptHeight * hIndex * m_compressionFactor / m_numRows);

				for(int rIndex = 0; rIndex < m_numColumns; rIndex++)
				{
					double theta = 2.0f * PI * rIndex / m_numColumns;

					double x = cos(theta) * m_cryptRadius;
					double z = sin(theta) * m_cryptRadius;

					Vector3D pos = m_pos;// = new Vector3d(cryptX * m_initialCryptSeparation - centeringOffset, -1.0f * CryptHeight, cryptY * m_initialCryptSeparation - centeringOffset);
					pos.x += x;
					pos.y -= m_cryptHeight;
					pos.y += height;
					pos.z += z;

					CellBox* box = m_grid.FindBox(pos);
					CellReference ref;
					MutationData noMutation = { false, false, false, 1.0, 1.0, 1.0 };

					box->AddCell(pos,
						pos,
						0.0f,
						m_cellSize,
						(double)rand() / RAND_MAX * -10.0f * m_averageGrowthTimesteps, 
						//0,
						(int)m_normalRNG->Next(),
						ref, 
						CellCycleStages::G0,
						noMutation,
						cryptId,
						0);
				}
			}
		}


	/***********************************************************************************************

	Various cell cycle update functions, should be fairly self-explanatory.

	***********************************************************************************************/
	void EnterG1(CellBox& box, int cellId)
	{
		box.m_cycleStages[cellId] = CellCycleStages::G1;
		box.m_currentStageNumTimesteps[cellId] = 0;
	}

	void DoBasicG0Phase(CellBox& box, int cellId, int timestep)
	{
		if(box.m_cycleStages[cellId] == CellCycleStages::G0)
		{
			box.m_currentStageNumTimesteps[cellId]++;

			if (box.m_positions[cellId].y < m_basicG0StemBoundary)
			{
				if (box.m_currentStageNumTimesteps[cellId] > m_requiredG0TimestepsStem * box.m_mutations[cellId].quiesceneceMultiplyer)
				{
					EnterG1(box, cellId);
					box.m_stemExitTimestep[cellId] = timestep;
				}
			}
			else if (box.m_positions[cellId].y < m_basicG0ProliferationBoundary)// || box.m_mutations[cellId].mutateQuiecence == true)
			{
				if (box.m_currentStageNumTimesteps[cellId] > m_requiredG0TimestepsProliferation)
				{
					EnterG1(box, cellId);
					box.m_stemExitTimestep[cellId] = timestep;
					
				}
			}
		}
	}

	void EnterMPhase(CellBox& box, int cellId)
	{
		box.m_cycleStages[cellId] = CellCycleStages::M;
		box.m_currentStageNumTimesteps[cellId] = 0;

		Vector3D newPos = box.m_positions[cellId];
		newPos.x += (5.0f - ((double)rand() / RAND_MAX * 10.0f)) * 1.0f;
		newPos.y += (5.0f - ((double)rand() / RAND_MAX * 10.0f)) * 1.0f;
		newPos.z += (5.0f - ((double)rand() / RAND_MAX * 10.0f)) * 1.0f;

		if (newPos.y < -1.0f * m_cryptHeight)
		{
			newPos.y = -1.0f * m_cryptHeight + 0.1f;
		}

		CellReference cellRef;
		cellRef.m_active = true;
		cellRef.m_box = &box;
		cellRef.m_cellId = cellId;

		int newCellId = box.AddCell(newPos,
			newPos,
			0.0f,
			m_cellSize / m_MPhaseTimesteps,
			0,
			(int)m_normalRNG->Next(),
			cellRef,
			CellCycleStages::Child,
			box.m_mutations[cellId],
			box.m_originCrypts[cellId],
			box.m_stemExitTimestep[cellId]);

		box.m_growthStageNumTimesteps[cellId] = (int)m_normalRNG->Next();

		box.m_otherSubCellIndex[cellId].m_active = true;
		box.m_otherSubCellIndex[cellId].m_box = &box;
		box.m_otherSubCellIndex[cellId].m_cellId = newCellId;
	}

	void DoGrowthPhase(CellBox& box, int cellId)
	{
		if (box.m_cycleStages[cellId] == CellCycleStages::G1)
		{
			box.m_currentStageNumTimesteps[cellId]++;

			double lerpVal = (double)box.m_currentStageNumTimesteps[cellId] / (double)box.m_growthStageNumTimesteps[cellId];
			box.m_radii[cellId] = m_cellSize * (1.0f - lerpVal) + m_cellSize * lerpVal * sqrt(2.0f);

			if (box.m_currentStageNumTimesteps[cellId] > box.m_growthStageNumTimesteps[cellId])
			{
				EnterMPhase(box, cellId);
			}
		}	
	}

	void DoMPhase(CellBox& box, int cellId)
	{
		if (box.m_cycleStages[cellId] == CellCycleStages::M)
		{
			box.m_currentStageNumTimesteps[cellId]++;

			CellReference& childIndex = box.m_otherSubCellIndex[cellId];

			double lerpVal = box.m_currentStageNumTimesteps[cellId] / m_MPhaseTimesteps;
			childIndex.m_box->m_radii[childIndex.m_cellId] = m_cellSize * lerpVal;
			box.m_radii[cellId] = m_cellSize * lerpVal + m_cellSize * sqrt(2.0f) * (1.0f - lerpVal);

			if (box.m_currentStageNumTimesteps[cellId] > m_MPhaseTimesteps)
			{
				box.m_currentStageNumTimesteps[cellId] = 0;
				box.m_cycleStages[cellId] = CellCycleStages::G0;
				box.m_radii[cellId] = m_cellSize;

				childIndex.m_box->m_currentStageNumTimesteps[childIndex.m_cellId] = 0;
				childIndex.m_box->m_cycleStages[childIndex.m_cellId] = CellCycleStages::G0;
				childIndex.m_box->m_radii[childIndex.m_cellId] = m_cellSize;

				box.m_otherSubCellIndex[cellId].m_active = false;
				childIndex.m_box->m_otherSubCellIndex[childIndex.m_cellId].m_active = false;

				m_numBirthEvents++;
			}
		}
	}

	/***********************************************************************************************

	If a cell has moved from one cell on the grid to another, move it

	***********************************************************************************************/
	void AssignCellToGrid(CellBox& box, int cellId)
	{
		CellBox* newBox = m_grid.FindBox(box.m_positions[cellId]);

		if(&box != newBox)
		{
			newBox->CopyCell(box, cellId);
			box.RemoveCell(cellId);
		}
	}

	/****************************************************************************************************

	Find the nearest point (and it's normal) on the membrane to a given position.  Finds what segment of
	the membrane (base, walls, or mouth) by height, then project to membrane depending on geomotry of
	segment.

	****************************************************************************************************/
	void GetClosestPointOnMembrane(Vector3D inputPosition, Vector3D& outputPosition, Vector3D& outputNormal)
	{
		inputPosition -= m_pos;
		Vector2D pos2d(inputPosition.x, inputPosition.z);

		if (pos2d.Length() > m_cryptRadius + m_flutingRadius)
		{
			outputPosition = inputPosition;
			outputPosition.y = 0.0f;
			outputNormal = Vector3D(0.0f, 1.0f, 0.0f);
		}
		else if (inputPosition.y > m_flutingRadius * -1.0f)
		{
			Vector2D virtualSphereDirection = pos2d;
			virtualSphereDirection /= virtualSphereDirection.Length();
			virtualSphereDirection *= m_cryptRadius + m_flutingRadius;

			Vector3D virtualSpherePosition(virtualSphereDirection.x, m_flutingRadius * -1.0f, virtualSphereDirection.y);

			Vector3D sphereRelativeCellPosition = inputPosition - virtualSpherePosition;

			outputNormal = sphereRelativeCellPosition / sphereRelativeCellPosition.Length();

			sphereRelativeCellPosition /= sphereRelativeCellPosition.Length();
			sphereRelativeCellPosition *= m_flutingRadius;

			outputPosition = virtualSpherePosition + sphereRelativeCellPosition;
		}
		else if (inputPosition.y > (m_cryptHeight - m_cryptRadius) * -1.0f)
		{
			Vector2D final;
			double length = pos2d.Length();
			Vector2D normalised = pos2d /length;
			final = normalised * m_cryptRadius;

			outputPosition.x = final.x;
			outputPosition.y = inputPosition.y;
			outputPosition.z = final.y;

			outputNormal.x = pos2d.x * -1.0f;
			outputNormal.y = 0.0f;
			outputNormal.z = pos2d.y * -1.0f;
			outputNormal /= outputNormal.Length();
		}
		else
		{
			Vector3D nicheCentre(0.0f, (m_cryptHeight - m_cryptRadius) * -1.0f, 0.0f);
			Vector3D normalisedPositionRelativeToNicheCentre = inputPosition - nicheCentre;
			normalisedPositionRelativeToNicheCentre = normalisedPositionRelativeToNicheCentre / normalisedPositionRelativeToNicheCentre.Length();
			outputPosition = normalisedPositionRelativeToNicheCentre * m_cryptRadius + nicheCentre;
			outputNormal = normalisedPositionRelativeToNicheCentre * -1.0f;
		}
		outputPosition += m_pos;
	}

	/******************************************************************************************************************************

	Membrane attachment code, find closest point on membrane and use the damped spring function to move towards it.

	******************************************************************************************************************************/
	void EnforceCryptWalls(CellBox& box, int cellId)
	{
		Vector3D pos = box.m_positions[cellId];

		// guard against 0 length vector division
		if (pos.x == 0.0f && pos.z == 0.0f)
		{
			pos.x = 0.1f;
		}

		// Don't fall through the bottom of the crypt
		if (pos.y < -1.0f * m_cryptHeight)
		{
			pos.y = -1.0f * m_cryptHeight + 10.0f;
		}

		Vector3D normal;
		Vector3D membranePos;
		GetClosestPointOnMembrane(pos, membranePos, normal);

		Vector3D delta = box.m_positions[cellId] - membranePos;

		box.m_offMembraneDistances[cellId] = delta.Length();


		bool isAboveBasementMembrane = Vector3D::DotProduct(delta, normal) > 0.0f;

		if (isAboveBasementMembrane == false)
		{
			box.m_offMembraneDistances[cellId] *= -1.0f;
			delta *= m_stromalRestorationFactor;
		}
		else
		{
			double mutationFactor = box.m_mutations[cellId].attachmentMultiplyer;

			delta *= std::min(m_offMembraneRestorationFactor * mutationFactor, 1.0);
		}

		box.m_positions[cellId] -= delta;
		box.m_onMembranePositions[cellId] = membranePos;
	}

	/************************************************************************************************

	Anoikis code, if a cell gets too far from the membrane it dies.  Some complicated stuff to
	handle cells that die while dividing.

	************************************************************************************************/
	bool DoAnoikis(CellBox& box, int cellId, int timestep)
	{
		if (box.m_offMembraneDistances[cellId] > m_membraneSeparationToTriggerAnoikis)
		{
			if (box.m_cycleStages[cellId] == CellCycleStages::M || box.m_cycleStages[cellId] == CellCycleStages::Child)
			{
				CellBox* otherBox = box.m_otherSubCellIndex[cellId].m_box;
				int indexInOtherBox = box.m_otherSubCellIndex[cellId].m_cellId;

				double y = otherBox->m_positions[indexInOtherBox].y;
				int yPercent = (int)((y - 250) / (m_cryptHeight + 250) * 100.0f);
				yPercent *= -1;
				m_anoikisHeights[yPercent]++;

				otherBox->KillCell(indexInOtherBox);
			}

			//deadcells.push_back(box.m_positions[cellId]);
			
			double y = box.m_positions[cellId].y;
			int yPercent = (int)((y - 250) / (m_cryptHeight + 250) * 100.0f);
			yPercent *= -1;
			m_anoikisHeights[yPercent]++;

			if(m_numAnoikisEvents % 100 == 0)
			{
				m_migrationTimes.push_back(timestep - box.m_stemExitTimestep[cellId]);
			}

			box.KillCell(cellId);
			m_numAnoikisEvents++;

			return true;
		}
		return false;
	}

	/******************************************************************************************

	Handle cells that move to the colon boundary, currently kills them but also possible to
	reflect them back into the simulation.  Experiments show that killing cells at the boundary
	gives the most realistic results compared to a very large simulation.

	******************************************************************************************/
	void EnforceColonBoundary(CellBox& box, int cellId)
	{
		Vector3D& pos = box.m_positions[cellId];

		if (pos.x > m_colonBoundary.x)
		{
			double delta = pos.x - m_colonBoundary.x;
			delta *= m_colonBoundaryRepulsionFactor;
			//pos.x -= delta;
			box.KillCell(cellId);
		}
		if (pos.x < (-1.0f * m_colonBoundary.x))
		{
			double delta = pos.x - (-1.0f * m_colonBoundary.x);
			delta *= m_colonBoundaryRepulsionFactor;
			//pos.x -= delta;
			box.KillCell(cellId);
		}
		if (pos.z > m_colonBoundary.y)
		{
			double delta = pos.z - m_colonBoundary.y;
			delta *= m_colonBoundaryRepulsionFactor;
			//pos.z -= delta;
			box.KillCell(cellId);
		}
		if (pos.z < (-1.0f * m_colonBoundary.y))
		{
			double delta = pos.z - (-1.0f * m_colonBoundary.y);
			delta *= m_colonBoundaryRepulsionFactor;
			//pos.z -= delta;
			box.KillCell(cellId);
		}
	}

	/**************************************************************************

	Call the various cell update functions above to perform a complete update

	**************************************************************************/
	void UpdateCell(CellBox& box, int cellId, int timestep)
	{
		DoBasicG0Phase(box, cellId, timestep);
		DoGrowthPhase(box, cellId);
		DoMPhase(box, cellId);
		EnforceCryptWalls(box, cellId);
		EnforceColonBoundary(box, cellId);
		AssignCellToGrid(box, cellId);
		m_cellularity++;
	}


	/***************************************************************************

	Loop over all cells and update, needs to be done in this order to make sure
	stuff doesn't move before being referenced.

	***************************************************************************/
	void UpdateCells(int timestep)
	{
		m_cellularity = 0;
		for(int col = 0; col < (int)m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = m_grid.m_columns[col];
			for(int row = 0; row < (int)column.size(); row++)
			{
				CellBox& box = column[row];
				for(int cell = 0; cell < (int)box.m_positions.size(); cell++)
				{
					UpdateCell(box, cell, timestep);
				}
			}
		}
		for(int col = 0; col < (int)m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = m_grid.m_columns[col];
			for(int row = 0; row < (int)column.size(); row++)
			{
				CellBox& box = column[row];
				for(int cell = 0; cell < (int)box.m_positions.size(); cell++)
				{
					DoAnoikis(box, cell, timestep);
				}
			}
		}
		for(int col = 0; col < (int)m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = m_grid.m_columns[col];
			for(int row = 0; row < (int)column.size(); row++)
			{
				m_grid.m_columns[col][row].KillDeadCells();
			}
		}
	}

	void ClearCounters()
	{
		m_numBirthEvents = 0;
		m_numAnoikisEvents = 0;
	}

	void Step(int timestep)
	{
		m_grid.Step();
		UpdateCells(timestep);
	}

	void GetCounts(int& cellulairty, int& stemCount, int& stemCycleCount, int& proliferationCount, int& proliferationCycleCount, int& mutatedFlatMucosaCount, int& normalFlatMucosaCount, int& mutatedCryptCount, int& normalCryptCount)
	{
		cellulairty = m_cellularity;
		stemCount = 0;
		stemCycleCount = 0;
		proliferationCount = 0;
		proliferationCycleCount = 0;
		mutatedFlatMucosaCount = 0;
		normalFlatMucosaCount = 0;
		mutatedCryptCount = 0;
		normalCryptCount = 0;

		for(int col = 0; col < (int)m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = m_grid.m_columns[col];
			for(int row = 0; row < (int)column.size(); row++)
			{
				CellBox& box = column[row];
				for(int cell = 0; cell < (int)box.m_positions.size(); cell++)
				{
					if (box.m_positions[cell].y < m_basicG0StemBoundary)
					{
						stemCount++;
						if(box.m_cycleStages[cell] == CellCycleStages::G1 || box.m_cycleStages[cell] == CellCycleStages::M)
						{
							stemCycleCount++;
						}
					}
					else if(box.m_positions[cell].y < m_basicG0ProliferationBoundary)
					{
						proliferationCount++;
						if(box.m_cycleStages[cell] == CellCycleStages::G1 || box.m_cycleStages[cell] == CellCycleStages::M)
						{
							proliferationCycleCount++;
						}
					}
					if(box.m_mutations[cell].mutateAttachment == true || box.m_mutations[cell].mutateCellForces == true || box.m_mutations[cell].mutateQuiecence == true)
					{
						if(box.m_positions[cell].y > m_flutingRadius * -1.0f)
						{
							mutatedFlatMucosaCount++;
						}
						else
						{
							mutatedCryptCount++;
						}						
					}
					else
					{
						
						if(box.m_positions[cell].y > m_flutingRadius * -1.0f)
						{
							normalFlatMucosaCount++;
						}
						else
						{
							normalCryptCount++;
						}						
					}
				}
			}
		}
	}
};