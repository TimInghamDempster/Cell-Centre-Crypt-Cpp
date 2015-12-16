
struct  Crypt
{
	Cells cellData;

	int m_numRows;
	int m_numColumns;

	void Init(int numRows, int numColumns)
	{
		m_numRows = numRows;
		m_numColumns = numColumns;

		int numCellsToReserve = numRows * numColumns * 10;

		cellData.upperBound = numCellsToReserve - 1;
		cellData.lowerBound = numCellsToReserve - 1;

		cellData.positionsX = (float*)malloc(numCellsToReserve * sizeof(float));
		cellData.positionsY = (float*)malloc(numCellsToReserve * sizeof(float));
		cellData.positionsZ = (float*)malloc(numCellsToReserve * sizeof(float));

		cellData.onMembranePositionsX = (float*)malloc(numCellsToReserve * sizeof(float));
		cellData.onMembranePositionsY = (float*)malloc(numCellsToReserve * sizeof(float));
		cellData.onMembranePositionsZ = (float*)malloc(numCellsToReserve * sizeof(float));

		cellData.radii = (float*)malloc(numCellsToReserve * sizeof(float));

		cellData.currentStageNumTimesteps = (int*)malloc(numCellsToReserve * sizeof(int));
		cellData.growthStageRequiredTimesteps = (int*)malloc(numCellsToReserve * sizeof(int));

		cellData.otherSubCellIndex = (int*)malloc(numCellsToReserve * sizeof(int));

		cellData.cycleStages = (CellCycleStages::Stages*)malloc(numCellsToReserve * sizeof(CellCycleStages::Stages));

		cellData.deadCellCount = 0;
		cellData.deadCells = (int*)malloc(numCellsToReserve * sizeof(int));

		cellData.AddNewCell();
	}

	void Step()
	{
		for(int i = cellData.lowerBound; i < cellData.upperBound; i++)
		{
			cellData.UpdateCell(i);
		}

		cellData.RemoveDeadCells();
	}

	void CleanUp()
	{
		free(cellData.positionsX);
		free(cellData.positionsY);
		free(cellData.positionsZ);

		free(cellData.onMembranePositionsX);
		free(cellData.onMembranePositionsY);
		free(cellData.onMembranePositionsZ);

		free(cellData.radii);

		free(cellData.currentStageNumTimesteps);
		free(cellData.growthStageRequiredTimesteps);
		free(cellData.otherSubCellIndex);

		free(cellData.cycleStages);
	}
};