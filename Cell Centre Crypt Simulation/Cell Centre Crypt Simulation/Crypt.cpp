
struct  Crypt
{
	CylindricalGrid m_grid;

	int m_numRows;
	int m_numColumns;

	void Init(int numRows, int numColumns)
	{
		m_numRows = numRows;
		m_numColumns = numColumns;

		m_grid.Init(numRows / 2, numColumns / 2, numRows * 2);
	}

	void Step()
	{
		m_grid.Step();
	}

	void CleanUp()
	{
		m_grid.CleanUp();
	}
};