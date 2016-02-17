
struct CellBox;

struct CellReference
{
	CellBox* m_box;
	int m_cellId;
	bool m_active;

	CellReference() :
		m_box(nullptr),
		m_cellId(-1),
		m_active(false)
	{
	}
};

struct CellBox
{
	std::vector<Vector3D> m_positions;
	std::vector<Vector3D> m_onMembranePositions;
	std::vector<double> m_offMembraneDistances;
	std::vector<double> m_radii;
	std::vector<int> m_currentStageNumTimesteps;
	std::vector<int> m_growthStageNumTimesteps;
	std::vector<CellReference> m_otherSubCellIndex; // This is going to be a pain to keep synchronised - pay extra attention to it
	std::vector<CellCycleStages::Stages> m_cycleStages;
	std::vector<CellBox*> m_potentialCollisionBoxes;
	std::vector<int> m_deathList;

	CellBox(int expectedNumberOfCells)
	{
		int reserveSize = expectedNumberOfCells * 10;
		m_positions.reserve(reserveSize);
		m_onMembranePositions.reserve(reserveSize);
		m_offMembraneDistances.reserve(reserveSize);
		m_radii.reserve(reserveSize);
		m_currentStageNumTimesteps.reserve(reserveSize);
		m_growthStageNumTimesteps.reserve(reserveSize);
		m_otherSubCellIndex.reserve(reserveSize);
		m_cycleStages.reserve(reserveSize);
		m_deathList.reserve(reserveSize);
	}

	int AddCell(Vector3D position,
				Vector3D onMembranePosition,
				double offMembraneDistance,
				double radius,
				int currentStageTimesteps,
				int growthStageTimesteps,
				CellReference otherSubCellIndex,
				CellCycleStages::Stages cycleStage)
	{
		m_positions.push_back(position);
		m_onMembranePositions.push_back(onMembranePosition);
		m_offMembraneDistances.push_back(offMembraneDistance);
		m_radii.push_back(radius);
		m_currentStageNumTimesteps.push_back(currentStageTimesteps);
		m_growthStageNumTimesteps.push_back(growthStageTimesteps);
		m_otherSubCellIndex.push_back(otherSubCellIndex);
		m_cycleStages.push_back(cycleStage);

		if(otherSubCellIndex.m_active == true)
		{
			CellBox* otherBox = otherSubCellIndex.m_box;
			int indexInOtherBox = otherSubCellIndex.m_cellId;
			CellReference& backReference = otherBox->m_otherSubCellIndex[indexInOtherBox];
			backReference.m_box = this;
			backReference.m_cellId = m_positions.size() - 1;
		}

		return m_positions.size() - 1;
	}

	void CopyCell(CellBox& box, int cellId)
	{
		AddCell(box.m_positions[cellId],
			box.m_onMembranePositions[cellId],
			box.m_offMembraneDistances[cellId],
			box.m_radii[cellId],
			box.m_currentStageNumTimesteps[cellId],
			box.m_growthStageNumTimesteps[cellId],
			box.m_otherSubCellIndex[cellId],
			box.m_cycleStages[cellId]);
	}

	void RemoveCell(int cellId)
	{
		int last = m_positions.size() - 1;

		m_positions[cellId] = m_positions[last];
		m_positions.pop_back();
		m_onMembranePositions[cellId] = m_onMembranePositions[last];
		m_onMembranePositions.pop_back();
		m_offMembraneDistances[cellId] = m_offMembraneDistances[last];
		m_offMembraneDistances.pop_back();
		m_radii[cellId] = m_radii[last];
		m_radii.pop_back();
		m_currentStageNumTimesteps[cellId] = m_currentStageNumTimesteps[last];
		m_currentStageNumTimesteps.pop_back();
		m_growthStageNumTimesteps[cellId] = m_growthStageNumTimesteps[last];
		m_growthStageNumTimesteps.pop_back();
		m_otherSubCellIndex[cellId] = m_otherSubCellIndex[last];
		m_otherSubCellIndex.pop_back();
		m_cycleStages[cellId] = m_cycleStages[last];
		m_cycleStages.pop_back();

		if(cellId < (int)m_otherSubCellIndex.size() && m_otherSubCellIndex[cellId].m_active)
		{
			CellBox* otherBox = m_otherSubCellIndex[cellId].m_box;
			int indexInOtherBox = m_otherSubCellIndex[cellId].m_cellId;
			CellReference& backReference = otherBox->m_otherSubCellIndex[indexInOtherBox];
			backReference.m_cellId = cellId;
		}

		for(int j = 0; j < (int)m_deathList.size(); j++)
		{
			if(m_deathList[j] == last)
			{
				m_deathList[j] = cellId;
			}
		}
	}

	void KillCell(int cellId)
	{
		if(std::find(m_deathList.begin(), m_deathList.end(), cellId) == m_deathList.end()) // Protect against double entry (ie cell and child cell both meet anoikis conditions)
		{
			m_deathList.push_back(cellId);
		}
	}

	void KillDeadCells()
	{
		for(int i = 0; i < (int)m_deathList.size(); i++)
		{
			int cellId = m_deathList[i];
			int last = m_positions.size() - 1;

			m_positions[cellId] = m_positions[last];
			m_positions.pop_back();
			m_onMembranePositions[cellId] = m_onMembranePositions[last];
			m_onMembranePositions.pop_back();
			m_offMembraneDistances[cellId] = m_offMembraneDistances[last];
			m_offMembraneDistances.pop_back();
			m_radii[cellId] = m_radii[last];
			m_radii.pop_back();
			m_currentStageNumTimesteps[cellId] = m_currentStageNumTimesteps[last];
			m_currentStageNumTimesteps.pop_back();
			m_growthStageNumTimesteps[cellId] = m_growthStageNumTimesteps[last];
			m_growthStageNumTimesteps.pop_back();
			m_otherSubCellIndex[cellId] = m_otherSubCellIndex[last];
			m_otherSubCellIndex.pop_back();
			m_cycleStages[cellId] = m_cycleStages[last];
			m_cycleStages.pop_back();

			if(cellId < (int)m_otherSubCellIndex.size() && m_otherSubCellIndex[cellId].m_active)
			{
				CellBox* otherBox = m_otherSubCellIndex[cellId].m_box;
				int indexInOtherBox = m_otherSubCellIndex[cellId].m_cellId;
				CellReference& backReference = otherBox->m_otherSubCellIndex[indexInOtherBox];
				backReference.m_cellId = cellId;
			}

			for(int j = i + 1; j < (int)m_deathList.size(); j++)
			{
				if(m_deathList[j] == last)
				{
					m_deathList[j] = cellId;
				}
			}
		}
		m_deathList.clear();
	}
};