
struct  Crypt
{
	CylindricalGrid m_grid;

	int m_numRows;
	int m_numColumns;

	Crypt(int numRows, int numColumns) : 
		m_grid(numRows / 2, numColumns / 2, numRows * 2, 4, 100.0f)
	{
		m_numRows = numRows;
		m_numColumns = numColumns;

		Vector3D pos(1.0f, 0.0f, 0.0f);
		CellBox* box = m_grid.FindBox(pos);
		box->AddCell(pos, pos, 0.0f, 0, 0, 0, CellCycleStages::G0);

		pos = Vector3D(-1.0f, 2.0f, -0.0f);
		box = m_grid.FindBox(pos);
		box->AddCell(pos, pos, 0.0f, 0, 0, 0, CellCycleStages::G0);
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
	}

	void DoGrowthPhase(CellBox& box, int cellId)
	{
		if (box.m_cycleStages[cellId] == CellCycleStages::G1)
		{

			box.m_currentStageNumTimesteps[cellId]++;

			float lerpVal = box.m_currentStageNumTimesteps[cellId]++ / box.m_growthStageNumTimesteps[cellId]++;
			box.m_radii[cellId] = m_cellSize * (1.0f - lerpVal) + CellSize * lerpVal * sqrt(2.0f);

			if (box.m_currentStageNumTimesteps[cellId] > box.m_growthStageNumTimesteps[cellId])
			{
				EnterMPhase(box, cellId);
			}
		}	
	}

	void DoMPhase(CellBox& box, int cellId)
	{
	}

	void AssignCellsToGrid(CellBox& box, int cellId)
	{
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
		else if (inputPosition.y > (CryptHeight - m_cryptRadius) * -1.0f)
		{
			Vector2D final;
			Vector2D normalised = pos2d / pos2d.Length();
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
			Vector3D nicheCentre(0.0f, (CryptHeight - m_cryptRadius) * -1.0f, 0.0f);
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
		if (pos.y < -1.0f * CryptHeight)
		{
			pos.y = -1.0f * CryptHeight + 10.0f;
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

	void DoAnoikis(CellBox& box, int cellId)
	{
		if (box.m_offMembraneDistances[cellId] > m_membraneSeparationToTriggerAnoikis)
		{
			if (box.m_cycleStages[cellId] == CellCycleStages::M || box.m_cycleStages[cellId] == CellCycleStages::Child)
			{
				m_cells.Remove(m_cells.ChildPointIndices[i]);
			}
			box.RemoveCell(cellId);
			m_numAnoikisEvents++;
		}
	}

	void EnforceColonBoundary(CellBox& box, int cellId)
	{
		Vector3D& pos = box.m_positions[cellId];

		if (pos.x > m_colonBoundary.X)
		{
			float delta = pos.x - m_colonBoundary.X;
			delta *= m_colonBoundaryRepulsionFactor;
			pos.x -= delta;
		}
		if (pos.x < (-1.0f * m_colonBoundary.X))
		{
			float delta = pos.x - (-1.0f * m_colonBoundary.X);
			delta *= m_colonBoundaryRepulsionFactor;
			pos.x -= delta;
		}
		if (pos.z > m_colonBoundary.Y)
		{
			float delta = pos.z - m_colonBoundary.Y;
			delta *= m_colonBoundaryRepulsionFactor;
			pos.z -= delta;
		}
		if (pos.z < (-1.0f * m_colonBoundary.Y))
		{
			float delta = pos.z - (-1.0f * m_colonBoundary.Y);
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
		EnforceCryptWalls(box, cellId);
		DoAnoikis(box, cellId);
		EnforceColonBoundary(box, cellId);
	}

	void UpdateCells()
	{
		for(int col = 0; col < m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = m_grid.m_columns[col];
			for(int row = 0; row < column.size(); row++)
			{
				CellBox& box = column[row];
				for(int cell = 0; cell < box.m_positions.size(); cell++)
				{
					UpdateCell(box, cell);
				}
			}
		}
	}

	void Step()
	{
		m_grid.Step();
		UpdateCells();
	}
};