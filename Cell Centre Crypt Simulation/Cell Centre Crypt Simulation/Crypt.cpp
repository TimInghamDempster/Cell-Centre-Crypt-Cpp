
struct  Crypt
{
	CylindricalGrid m_grid;

	int m_numRows;
	int m_numColumns;

	Crypt(int numRows, int numColumns) : 
		m_grid(numRows / 2, numColumns / 2, numRows * 2, 4, 100.0f)
	{
		m_numRows = numRows;
		m_numColumns = numColumns;

		Vector3D pos(1.0f, 0.0f, 0.0f);
		CellBox* box = m_grid.FindBox(pos);
		box->AddCell(pos, pos, 0.0f, 0, 0, 0, CellCycleStages::G0);

		pos = Vector3D(-1.0f, 2.0f, -0.0f);
		box = m_grid.FindBox(pos);
		box->AddCell(pos, pos, 0.0f, 0, 0, 0, CellCycleStages::G0);
	}

	void Step()
	{
		m_grid.Step();
	}
};