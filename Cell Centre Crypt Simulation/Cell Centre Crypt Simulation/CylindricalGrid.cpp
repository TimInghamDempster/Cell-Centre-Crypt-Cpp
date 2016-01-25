
struct FenceId
{
	int row;
	int column;

	FenceId()
	{
		row = -1;
		column = -1;
	}
};

struct CGridColumn
{
	int* m_boxFences;
	Cells m_cells;

	int m_capacity;
};

struct CylindricalGrid
{
	CGridColumn* m_columns;
	int m_numColumns;
	int m_numRows;

	FenceId FindFenceAbove(float x, float y, float z)
	{
		FenceId id;
		return id;
	}

	void Step()
	{

	}

	int GetFenceIndex(FenceId id)
	{
		return m_columns[id.column].m_boxFences[id.row];
	}

	void IncrementFenceIndex(FenceId id)
	{
		m_columns[id.column].m_boxFences[id.row]++;
	}

	void DecrementFenceIndex(FenceId id)
	{
		m_columns[id.column].m_boxFences[id.row]--;
	}

	void MoveBoxDownY(int cellToMove, int columnId)
	{
		CGridColumn& column = m_columns[columnId];

		FenceId fenceBelowCellToMove = FindFenceAbove(column.m_cells.positionsX[cellToMove], column.m_cells.positionsY[cellToMove], column.m_cells.positionsZ[cellToMove]);
		fenceBelowCellToMove.row--;
		int bottomCell = GetFenceIndex(fenceBelowCellToMove) + 1;

		column.m_cells.SwapCells(cellToMove, bottomCell); // Put the cell at the bottom of it's box
		IncrementFenceIndex(fenceBelowCellToMove); // Move the box boundary up one so bottom cell of box above is now in this box
	}

	void MoveBoxUpY(int cellToMove, int columnId)
	{
		CGridColumn& column = m_columns[columnId];

		FenceId fenceAboveCellToMove = FindFenceAbove(column.m_cells.positionsX[cellToMove], column.m_cells.positionsY[cellToMove], column.m_cells.positionsZ[cellToMove]);
		int topCell = GetFenceIndex(fenceAboveCellToMove);

		column.m_cells.SwapCells(cellToMove, topCell); // Put the cell at the top of it's box
		DecrementFenceIndex(fenceAboveCellToMove); // Move the box boundary down one so top cell is now in the box above
	}

	void Init(int numBoxesY, int numBoxesTheta, int expectedNumCellsPerColumn)
	{
		m_columns = new CGridColumn[numBoxesTheta];
		m_numColumns = numBoxesTheta;
		m_numRows = numBoxesY;

		for(int i = 0; i < numBoxesTheta; i++)
		{
			m_columns[i].m_cells.AllocateCells(expectedNumCellsPerColumn * 10);
			m_columns[i].m_capacity = expectedNumCellsPerColumn * 10;
			m_columns[i].m_boxFences = new int[numBoxesY + 1];
		}
	}

	void CleanUp()
	{
		for(int i = 0; i < m_numColumns; i++)
		{
			m_columns[i].m_cells.CleanUp();
			delete[] m_columns[i].m_boxFences;
		}
		delete[] m_columns;
	}
};