
struct BoxId
{
	int row;
	int column;

	BoxId()
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

	BoxId FindBox(float x, float y, float z)
	{
		BoxId id;
		return id;
	}

	int GetUpperIndex(BoxId id)
	{
		return m_columns[id.column].m_boxUpperBounds[id.row];
	}

	void IncrementUpperIndex(BoxId id)
	{
		m_columns[id.column].m_boxUpperBounds[id.row]++;
	}

	void DecrementUpperIndex(BoxId id)
	{
		m_columns[id.column].m_boxUpperBounds[id.row]--;
	}
};