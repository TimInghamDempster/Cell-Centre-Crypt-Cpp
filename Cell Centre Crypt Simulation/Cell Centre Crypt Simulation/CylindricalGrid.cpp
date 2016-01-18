
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
	int* m_boxUpperBounds;
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

	int GetFenceIndex(FenceId id)
	{
		return m_columns[id.column].m_boxUpperBounds[id.row];
	}

	void IncrementFenceIndex(FenceId id)
	{
		m_columns[id.column].m_boxUpperBounds[id.row]++;
	}

	void DecrementFenceIndex(FenceId id)
	{
		m_columns[id.column].m_boxUpperBounds[id.row]--;
	}
};