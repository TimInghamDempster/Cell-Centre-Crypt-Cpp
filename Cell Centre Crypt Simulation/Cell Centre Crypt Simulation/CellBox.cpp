
struct CellBox
{
	std::vector<Vector3D> m_positions;
	std::vector<Vector3D> m_onMembranePositions;
	std::vector<float> m_radii;
	std::vector<int> m_currentStageNumTimesteps;
	std::vector<int> m_growthStageNumTimesteps;
	std::vector<int> m_otherSubCellIndex; // This is going to be a pain to keep synchronised - pay extra attention to it
	std::vector<CellCycleStages::Stages> m_cycleStages;

	CellBox(int expectedNumberOfCells)
	{
		int reserveSize = expectedNumberOfCells * 10;
		m_positions.reserve(reserveSize);
		m_onMembranePositions.reserve(reserveSize);
		m_radii.reserve(reserveSize);
		m_currentStageNumTimesteps.reserve(reserveSize);
		m_growthStageNumTimesteps.reserve(reserveSize);
		m_otherSubCellIndex.reserve(reserveSize);
		m_cycleStages.reserve(reserveSize);
	}

	int AddCell(Vector3D position)
	{
		return 0;
	}
};