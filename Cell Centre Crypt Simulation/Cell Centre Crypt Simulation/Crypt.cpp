
struct  Crypt
{
	Cells m_cellData;
	Grid m_grid;

	int m_numRows;
	int m_numColumns;

	void Init(int numRows, int numColumns)
	{
		m_numRows = numRows;
		m_numColumns = numColumns;

		int numCellsToReserve = numRows * numColumns * 10;

		m_cellData.grid = &m_grid;

		m_cellData.upperBound = numCellsToReserve - 1;
		m_cellData.lowerBound = numCellsToReserve - 1;
		m_cellData.upperMemoryBound = numCellsToReserve - 1;

		m_cellData.positionsX = (float*)malloc(numCellsToReserve * sizeof(float));
		m_cellData.positionsY = (float*)malloc(numCellsToReserve * sizeof(float));
		m_cellData.positionsZ = (float*)malloc(numCellsToReserve * sizeof(float));

		m_cellData.onMembranePositionsX = (float*)malloc(numCellsToReserve * sizeof(float));
		m_cellData.onMembranePositionsY = (float*)malloc(numCellsToReserve * sizeof(float));
		m_cellData.onMembranePositionsZ = (float*)malloc(numCellsToReserve * sizeof(float));

		m_cellData.radii = (float*)malloc(numCellsToReserve * sizeof(float));

		m_cellData.currentStageNumTimesteps = (int*)malloc(numCellsToReserve * sizeof(int));
		m_cellData.growthStageRequiredTimesteps = (int*)malloc(numCellsToReserve * sizeof(int));

		m_cellData.otherSubCellIndex = (int*)malloc(numCellsToReserve * sizeof(int));

		m_cellData.cycleStages = (CellCycleStages::Stages*)malloc(numCellsToReserve * sizeof(CellCycleStages::Stages));

		m_cellData.deadCellCount = 0;
		m_cellData.deadCells = (int*)malloc(numCellsToReserve * sizeof(int));

		m_cellData.AddNewCell();
	}

	void Step()
	{
		for(int i = m_cellData.lowerBound; i < m_cellData.upperBound; i++)
		{
			m_cellData.UpdateCell(i);
		}

		m_cellData.RemoveDeadCells();
	}

	void CleanUp()
	{
		free(m_cellData.positionsX);
		free(m_cellData.positionsY);
		free(m_cellData.positionsZ);

		free(m_cellData.onMembranePositionsX);
		free(m_cellData.onMembranePositionsY);
		free(m_cellData.onMembranePositionsZ);

		free(m_cellData.radii);

		free(m_cellData.currentStageNumTimesteps);
		free(m_cellData.growthStageRequiredTimesteps);
		free(m_cellData.otherSubCellIndex);

		free(m_cellData.cycleStages);
	}
};