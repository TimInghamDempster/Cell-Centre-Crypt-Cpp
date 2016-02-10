
struct  Crypt
{

	int m_numRows;
	int m_numColumns;
	
	const float m_secondsPerTimestep;
	
	const float m_cryptRadius;
	const float m_flutingRadius;

	const float m_compressionFactor;
	const float m_cellSize;
	const float m_cryptHeight;
	
	const float m_basicG0ProliferationBoundary;
	const float m_basicG0StemBoundary;
	
	const float m_averageGrowthTimesteps;
	const float m_requiredG0TimestepsStem;
	const float m_requiredG0TimestepsProliferation;
	const float m_MPhaseTimesteps;

	const float m_colonBoundaryRepulsionFactor;
	const float m_offMembraneRestorationFactor;
	const float m_stromalRestorationFactor;
	const float m_membraneSeparationToTriggerAnoikis;

	Vector2D m_colonBoundary;

	std::default_random_engine& m_random_generator;
	std::normal_distribution<float> m_normalRNG;
	std::uniform_real_distribution<float> m_random;

	int m_numBirthEvents;
	int m_numAnoikisEvents;

	int m_cellularity;

	CylindricalGrid m_grid;

	Crypt(int numRows, int numColumns, std::default_random_engine& random, float averageGrowthTimeSeconds) : 
		m_numRows(numRows),
		m_numColumns(numColumns),
		m_secondsPerTimestep(30.0f),
		m_cryptRadius(500.0f),
		m_flutingRadius(500.0f),
		m_compressionFactor(1.9f),
		m_cellSize(m_cryptRadius * 2.0f * (float)PI / (numColumns * 2.0f)),
		m_cryptHeight((m_cellSize * 2.0f * numRows + m_cryptRadius + m_flutingRadius) / m_compressionFactor),
		m_basicG0ProliferationBoundary(m_cryptHeight * -0.7f),
		m_basicG0StemBoundary(m_cryptHeight * -0.95f),
		m_averageGrowthTimesteps(averageGrowthTimeSeconds / m_secondsPerTimestep),
		m_requiredG0TimestepsStem(m_averageGrowthTimesteps * 9.0f),
		m_requiredG0TimestepsProliferation(100.0f),
		m_MPhaseTimesteps(1238.4f / m_secondsPerTimestep),
		m_colonBoundaryRepulsionFactor(0.3f),
		m_offMembraneRestorationFactor(0.001f),
		m_stromalRestorationFactor(0.3f),
		m_membraneSeparationToTriggerAnoikis(100.0f),
		m_colonBoundary(1000.0f, 1000.0f),
		m_random_generator(random),
		m_random(0.0001f, 1.0f),
		m_normalRNG(m_averageGrowthTimesteps, 2.625f * 3600.0f / m_secondsPerTimestep),
		m_numBirthEvents(0),
		m_numAnoikisEvents(0),
		m_cellularity(0),
		m_grid(numRows / 2, numColumns / 2, numRows * 2, 4, m_cryptHeight, random, 1238.4f / m_secondsPerTimestep)
	{
		CellReference ref;
		Vector3D pos(0.0f, m_cryptHeight * -0.999f, 0.0f);
		CellBox* box = m_grid.FindBox(pos);
		//box->AddCell(pos, pos, 0.0f, m_cellSize, 0, (int)m_normalRNG(m_random_generator), ref, CellCycleStages::G0);
		PopulateCrypt();
	}

	void PopulateCrypt()
		{
			for(int hIndex = 1; hIndex < m_numRows / m_compressionFactor - 2; hIndex++)
			{
				float height = ( m_cryptHeight * hIndex * m_compressionFactor / m_numRows);

				for(int rIndex = 0; rIndex < m_numColumns; rIndex++)
				{
					float theta = 2.0f * PI * rIndex / m_numColumns;

					float x = cos(theta) * m_cryptRadius;
					float z = sin(theta) * m_cryptRadius;

					Vector3D pos;// = new Vector3d(cryptX * m_initialCryptSeparation - centeringOffset, -1.0f * CryptHeight, cryptY * m_initialCryptSeparation - centeringOffset);
					pos.x += x;
					pos.y -= m_cryptHeight;
					pos.y += height;
					pos.z += z;

					CellBox* box = m_grid.FindBox(pos);
					CellReference ref;

					box->AddCell(pos,
						pos,
						0.0f,
						m_cellSize,
						m_random(m_random_generator) * -10.0f * m_averageGrowthTimesteps, 
						//0,
						m_normalRNG(m_random_generator),
						ref, 
						CellCycleStages::G0);
					/*
					m_cells.AddCell(pos,
                               (float)(-m_averageGrowthTimesteps * m_random.NextDouble() * 10), // Randomise time of first division as we are jumping in part way through the simulation.
							   m_averageGrowthTimesteps,
							   m_baseColours[cryptColourIndex],
							   cryptColourIndex,
							   (UInt32)(cryptX + cryptY * m_numCryptsPerSide),
							   CellSize,
							   CellCycleStage.G0);*/
				}
			}
		}

	void EnterG1(CellBox& box, int cellId)
	{
		box.m_cycleStages[cellId] = CellCycleStages::G1;
		box.m_currentStageNumTimesteps[cellId] = 0;
	}

	void DoBasicG0Phase(CellBox& box, int cellId)
	{
		if(box.m_cycleStages[cellId] == CellCycleStages::G0)
		{
			box.m_currentStageNumTimesteps[cellId]++;

			if (box.m_positions[cellId].y < m_basicG0StemBoundary)
			{
				if (box.m_currentStageNumTimesteps[cellId] > m_requiredG0TimestepsStem)
				{
					EnterG1(box, cellId);
				}
			}
			else if (box.m_positions[cellId].y < m_basicG0ProliferationBoundary)
			{
				if (box.m_currentStageNumTimesteps[cellId] > m_requiredG0TimestepsProliferation)
				{
					EnterG1(box, cellId);
				}
			}
		}
	}

	void EnterMPhase(CellBox& box, int cellId)
	{
		box.m_cycleStages[cellId] = CellCycleStages::M;
		box.m_currentStageNumTimesteps[cellId] = 0;

		Vector3D newPos = box.m_positions[cellId];
		newPos.x += (5.0f - (m_random(m_random_generator) * 10.0f)) * 1.0f;
		newPos.y += (5.0f - (m_random(m_random_generator) * 10.0f)) * 1.0f;
		newPos.z += (5.0f - (m_random(m_random_generator) * 10.0f)) * 1.0f;

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
			(int)m_normalRNG(m_random_generator),
			cellRef,
			CellCycleStages::Child);

		box.m_growthStageNumTimesteps[cellId] = (int)m_normalRNG(m_random_generator);

		box.m_otherSubCellIndex[cellId].m_active = true;
		box.m_otherSubCellIndex[cellId].m_box = &box;
		box.m_otherSubCellIndex[cellId].m_cellId = newCellId;
	}

	void DoGrowthPhase(CellBox& box, int cellId)
	{
		if (box.m_cycleStages[cellId] == CellCycleStages::G1)
		{
			box.m_currentStageNumTimesteps[cellId]++;

			float lerpVal = (float)box.m_currentStageNumTimesteps[cellId] / (float)box.m_growthStageNumTimesteps[cellId];
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

			float lerpVal = box.m_currentStageNumTimesteps[cellId] / m_MPhaseTimesteps;
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

	void AssignCellToGrid(CellBox& box, int cellId)
	{
		CellBox* newBox = m_grid.FindBox(box.m_positions[cellId]);

		if(&box != newBox)
		{
			newBox->CopyCell(box, cellId);
			box.RemoveCell(cellId);
		}
	}

	void GetClosestPointOnMembrane(const Vector3D inputPosition, Vector3D& outputPosition, Vector3D& outputNormal)
	{
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
			float length = pos2d.Length();
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
	}

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
			delta *= m_offMembraneRestorationFactor;
		}

		box.m_positions[cellId] -= delta;
		box.m_onMembranePositions[cellId] = membranePos;
	}

	bool DoAnoikis(CellBox& box, int cellId)
	{
		if (box.m_offMembraneDistances[cellId] > m_membraneSeparationToTriggerAnoikis)
		{
			if (box.m_cycleStages[cellId] == CellCycleStages::M || box.m_cycleStages[cellId] == CellCycleStages::Child)
			{
				CellBox* otherBox = box.m_otherSubCellIndex[cellId].m_box;
				int indexInOtherBox = box.m_otherSubCellIndex[cellId].m_cellId;
				otherBox->KillCell(indexInOtherBox);
			}
			box.KillCell(cellId);
			m_numAnoikisEvents++;
			return true;
		}
		return false;
	}

	void EnforceColonBoundary(CellBox& box, int cellId)
	{
		Vector3D& pos = box.m_positions[cellId];

		if (pos.x > m_colonBoundary.x)
		{
			float delta = pos.x - m_colonBoundary.x;
			delta *= m_colonBoundaryRepulsionFactor;
			pos.x -= delta;
		}
		if (pos.x < (-1.0f * m_colonBoundary.x))
		{
			float delta = pos.x - (-1.0f * m_colonBoundary.x);
			delta *= m_colonBoundaryRepulsionFactor;
			pos.x -= delta;
		}
		if (pos.z > m_colonBoundary.y)
		{
			float delta = pos.z - m_colonBoundary.y;
			delta *= m_colonBoundaryRepulsionFactor;
			pos.z -= delta;
		}
		if (pos.z < (-1.0f * m_colonBoundary.y))
		{
			float delta = pos.z - (-1.0f * m_colonBoundary.y);
			delta *= m_colonBoundaryRepulsionFactor;
			pos.z -= delta;
		}
	}


	void UpdateCell(CellBox& box, int cellId)
	{
		DoBasicG0Phase(box, cellId);
		DoGrowthPhase(box, cellId);
		DoMPhase(box, cellId);
		EnforceCryptWalls(box, cellId);
		EnforceColonBoundary(box, cellId);
		AssignCellToGrid(box, cellId);
	}

	void UpdateCells()
	{
		for(int col = 0; col < (int)m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = m_grid.m_columns[col];
			for(int row = 0; row < (int)column.size(); row++)
			{
				CellBox& box = column[row];
				for(int cell = 0; cell < (int)box.m_positions.size(); cell++)
				{
					UpdateCell(box, cell);
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
					DoAnoikis(box, cell);
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

	void Step()
	{
		m_grid.Step();
		UpdateCells();
	}

	int Cellularity()
	{
		return m_cellularity;
	}
};