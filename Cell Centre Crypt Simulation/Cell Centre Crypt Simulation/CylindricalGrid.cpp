
struct CylindricalGrid
{
	std::vector<std::vector<CellBox> > m_columns;
	const int m_numColumns;
	const int m_numRows;
	const float m_height;
	const float m_boxHeight;
	const float m_cellStiffness;

	std::default_random_engine& m_random_generator;
	std::uniform_real_distribution<float> m_random;

	CylindricalGrid(int numBoxesY, int numBoxesTheta, int expectedNumCellsPerColumn, int expectedNumberOfCellsInBox, float height, std::default_random_engine& random_generator)
		:
		m_numColumns(numBoxesTheta),
		m_numRows(numBoxesY),
		m_height(height),
		m_boxHeight(height / numBoxesY),
		m_cellStiffness(0.03f),
		m_random_generator(random_generator)
	{
		m_columns = std::vector<std::vector<CellBox> > (numBoxesTheta, std::vector<CellBox> (numBoxesY, CellBox(expectedNumberOfCellsInBox)));
	}

	CellBox* FindBox(Vector3D position)
	{		
		float theta = atan2(position.z, position.x);
		float normalisedTheta = theta / (2.0f * (float)PI) + 0.5f; // Map from -PI < x < PI to 0 < x < 1
		float normalisedColumnWidth = 1.0f / (m_numColumns - 1);

		int column = (int)(normalisedTheta / normalisedColumnWidth);
		int row = (int)((position.y + m_height) / m_boxHeight);

		row = row >= 0 ? row : 0;
		row = row < m_numRows ? row : m_numRows - 1;

		return &m_columns[column][row]; // Garunteed safe because the column vector (and grid vector) never change.
	}

	void Step()
	{
		for(int colId = 0; colId < m_numColumns; colId++)
		{
			for(int rowId = 0; rowId < m_numRows; rowId++)
			{
				CellBox& box = m_columns[colId][rowId];

				for(int cellId = 0; cellId < (int)box.m_positions.size(); cellId++)
				{
					for(int innerCellId = cellId + 1; innerCellId < (int)box.m_positions.size(); innerCellId++)
					{
						{

							/*int cryptId1 = (int)m_cells.CryptIds[i];
							int cryptId2 = (int)m_cells.CryptIds[j];

							Vector3D cryptPos1 = m_crypts.m_cryptPositions[cryptId1];
							Vector3D cryptPos2 = m_crypts.m_cryptPositions[cryptId2];*/

							/* Use this version for spherical cells
							Vector3d outerPos = m_cells.Positions[i];
							Vector3d innerPos = m_cells.Positions[j];
							*/

							Vector3D outerPos = box.m_onMembranePositions[cellId];
							Vector3D innerPos = box.m_onMembranePositions[innerCellId];
							//Vector3d dummy;

							//GetClosestPointOnMembrane(m_cells.Positions[i] - cryptPos1, out outerPos, out dummy);
							//GetClosestPointOnMembrane(m_cells.Positions[j] - cryptPos2, out innerPos, out dummy);

							Vector3D delta = outerPos - innerPos;
							float separation = delta.Length();


							float targetSeparation = box.m_radii[cellId] + box.m_radii[innerCellId];

							//if (j == m_cells.ChildPointIndices[i])
							{
								//float growthFactor = m_cells.MStageCurrentTimesteps[i] / MStageRequiredTimesteps;
								//targetSeparation *= growthFactor;
							}
							/*else
							{
							if (m_cells.CycleStages[i] == CellCycleStage.Child)
							{
							int parentId = m_cells.ChildPointIndices[i];
							float growthFactor = m_cells.GrowthStageCurrentTimesteps[parentId] / m_cells.GrowthStageRequiredTimesteps[parentId];
							targetSeparation = m_cells.Radii[j] + m_cells.Radii[i] * growthFactor;
							}
							if (m_cells.CycleStages[j] == CellCycleStage.Child)
							{
							int parentId = m_cells.ChildPointIndices[j];
							float growthFactor = m_cells.GrowthStageCurrentTimesteps[parentId] / m_cells.GrowthStageRequiredTimesteps[parentId];
							targetSeparation = m_cells.Radii[i] + m_cells.Radii[j] * growthFactor;
							}
							}*/

							if (separation < targetSeparation)
							{
								float restitution = targetSeparation - separation;
								restitution *= m_cellStiffness;
								if (separation < 0.1f)
								{
									separation = 0.1f;
									delta.x = (float)m_random(m_random_generator) - 0.5f;
									delta.y = (float)m_random(m_random_generator) - 0.5f;
									delta.z = (float)m_random(m_random_generator) - 0.5f;
								}

								Vector3D force = delta * restitution / separation;
								/*Vector3D cryptForce = force;
								cryptForce.Y = 0.0f;

								m_crypts.m_cellularity[cryptId1]++;
								m_crypts.m_cellularity[cryptId2]++;

								if ((cryptPos1 - outerPos).Length() < m_cryptRadius + m_flutingRadius)
								{
									//m_crypts.m_forces[cryptId1] += cryptForce;
								}

								if ((cryptPos2 - innerPos).Length() < m_cryptRadius + m_flutingRadius)
								{
									//m_crypts.m_forces[cryptId2] -= cryptForce;
								}*/

								box.m_positions[cellId] += force;
								box.m_positions[innerCellId] -= force;
							}
						}
					}
				}
			}
		}
	}
};