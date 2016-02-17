
struct CylindricalGrid
{
	std::vector<std::vector<CellBox> > m_columns;
	const int m_numColumns;
	const int m_numRows;
	const double m_height;
	const double m_boxHeight;
	const double m_cellStiffness;
	const double m_MStageRequiredTimesteps;

	std::default_random_engine& m_random_generator;
	std::uniform_real_distribution<double> m_random;

	CylindricalGrid(int numBoxesY, int numBoxesTheta, int expectedNumCellsPerColumn, int expectedNumberOfCellsInBox, double height, std::default_random_engine& random_generator, double mStageRequiredTimesteps)
		:
		m_numColumns(numBoxesTheta),
		m_numRows(numBoxesY),
		m_height(height),
		m_boxHeight(height / numBoxesY),
		m_cellStiffness(0.3f),
		m_MStageRequiredTimesteps(mStageRequiredTimesteps),
		m_random_generator(random_generator)
	{
		m_columns = std::vector<std::vector<CellBox> > (numBoxesTheta, std::vector<CellBox> (numBoxesY, CellBox(expectedNumberOfCellsInBox)));

		for(int col = 0; col < m_numColumns; col++)
		{
			for(int row = 0; row < m_numRows; row++)
			{
				m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[col][row]);

				if(row == 0)
				{
					for(int innerCol = col + 1; innerCol < m_numColumns; innerCol++)
					{
						m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[innerCol][row]);
					}
				}

				if(row < m_numRows - 1)
				{
					m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[col][row + 1]);
				}

				
				if(col < m_numColumns - 1)
				{
						
					
					if(row < m_numRows - 1)
					{
						m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[col + 1][row + 1]);
					}

					if(row > 0)
					{
						m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[col + 1][row]);
						m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[col + 1][row - 1]);
					} 
				}
				else
				{
					
					if(row < m_numRows - 1)
					{
						m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[0][row + 1]);
					}

					if(row > 0)
					{
						m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[0][row]);
						m_columns[col][row].m_potentialCollisionBoxes.push_back(&m_columns[0][row - 1]);
					} 
				}
			}
			
		}
	}

	CellBox* FindBox(Vector3D position)
	{		
		double theta = atan2(position.z, position.x);
		double normalisedTheta = theta / (2.0f * (double)PI) + 0.5f; // Map from -PI < x < PI to 0 < x < 1
		double normalisedColumnWidth = 1.0f / m_numColumns;

		int column = (int)(normalisedTheta / normalisedColumnWidth);
		int row = (int)((position.y + m_height) / m_boxHeight);

		row = row >= 0 ? row : 0;
		row = row < m_numRows ? row : m_numRows - 1;

		column = column < m_numColumns ? column : m_numColumns - 1; // Only happens in very rare circumstaces, doubleing point issue.

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
					for(int collisionBoxId = 0; collisionBoxId < (int)box.m_potentialCollisionBoxes.size(); collisionBoxId++)
					{
						CellBox* collisionBox = box.m_potentialCollisionBoxes[collisionBoxId];

						int innnerCellStart = collisionBox != &box ? 0 : cellId + 1; // avoid double update when testing in same box

						for(int innerCellId = innnerCellStart; innerCellId < (int)collisionBox->m_positions.size(); innerCellId++)
						//for(int innerCellId = (int)collisionBox->m_positions.size() - 1; innerCellId >= innnerCellStart; innerCellId--)
						{


							/*int cryptId1 = (int)m_cells.CryptIds[i];
							int cryptId2 = (int)m_cells.CryptIds[j];

							Vector3D cryptPos1 = m_crypts.m_cryptPositions[cryptId1];
							Vector3D cryptPos2 = m_crypts.m_cryptPositions[cryptId2];*/

							// Use this version for spherical cells
							/*Vector3D outerPos = box.m_positions[cellId];
							Vector3D innerPos = collisionBox->m_positions[innerCellId];*/
							

							Vector3D outerPos = box.m_onMembranePositions[cellId];
							Vector3D innerPos = collisionBox->m_onMembranePositions[innerCellId];
							//Vector3d dummy;

							//GetClosestPointOnMembrane(m_cells.Positions[i] - cryptPos1, out outerPos, out dummy);
							//GetClosestPointOnMembrane(m_cells.Positions[j] - cryptPos2, out innerPos, out dummy);

							Vector3D delta = outerPos - innerPos;
							double separation = delta.Length();


							double targetSeparation = box.m_radii[cellId] + collisionBox->m_radii[innerCellId];

							CellReference& otherCell  = box.m_otherSubCellIndex[cellId];
							if (otherCell.m_active
								&& otherCell.m_box == collisionBox
								&& otherCell.m_cellId == innerCellId)
							{
								double growthFactor;
								
								if(box.m_cycleStages[cellId] == CellCycleStages::M)
								{
									growthFactor = box.m_currentStageNumTimesteps[cellId] / m_MStageRequiredTimesteps;
								}
								else
								{
									growthFactor = collisionBox->m_currentStageNumTimesteps[innerCellId] / m_MStageRequiredTimesteps;
								}
								
								targetSeparation *= growthFactor;
							}
							/*else
							{
							if (m_cells.CycleStages[i] == CellCycleStage.Child)
							{
							int parentId = m_cells.ChildPointIndices[i];
							double growthFactor = m_cells.GrowthStageCurrentTimesteps[parentId] / m_cells.GrowthStageRequiredTimesteps[parentId];
							targetSeparation = m_cells.Radii[j] + m_cells.Radii[i] * growthFactor;
							}
							if (m_cells.CycleStages[j] == CellCycleStage.Child)
							{
							int parentId = m_cells.ChildPointIndices[j];
							double growthFactor = m_cells.GrowthStageCurrentTimesteps[parentId] / m_cells.GrowthStageRequiredTimesteps[parentId];
							targetSeparation = m_cells.Radii[i] + m_cells.Radii[j] * growthFactor;
							}
							}*/

							if (separation < targetSeparation)
							{
								double restitution = targetSeparation - separation;
								restitution *= m_cellStiffness;
								if (separation < 0.1f)
								{
									separation = 0.1f;
									delta.x = (double)m_random(m_random_generator) - 0.5f;
									delta.y = (double)m_random(m_random_generator) - 0.5f;
									delta.z = (double)m_random(m_random_generator) - 0.5f;
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
								collisionBox->m_positions[innerCellId] -= force;
							}
						}
					}
				}
			}
		}
	}
};