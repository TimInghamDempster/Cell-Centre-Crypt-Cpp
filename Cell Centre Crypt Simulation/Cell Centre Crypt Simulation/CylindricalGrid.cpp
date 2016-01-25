
struct CylindricalGrid
{
	std::vector<std::vector<CellBox> > m_columns;
	int m_numColumns;
	int m_numRows;
	float m_boxHeight;
	
	CylindricalGrid(int numBoxesY, int numBoxesTheta, int expectedNumCellsPerColumn, int expectedNumberOfCellsInBox, float height)
	{
		m_columns = std::vector<std::vector<CellBox> > (numBoxesTheta, std::vector<CellBox> (numBoxesY, CellBox(expectedNumberOfCellsInBox)));
		m_numColumns = numBoxesTheta;
		m_numRows = numBoxesY;
		m_boxHeight = height / numBoxesY;
	}

	CellBox* FindBox(Vector3D position)
	{		
		float theta = atan2(position.z, position.x);
		float normalisedTheta = theta / (2.0f * (float)PI) + 0.5; // Map from -PI < x < PI to 0 < x < 1
		float normalisedColumnWidth = 1.0f / m_numColumns;

		int column = (int)(normalisedTheta / normalisedColumnWidth);
		int row = (int)(position.y / m_boxHeight);
		
		return &m_columns[column][row]; // Garunteed safe because the column vector (and grid vector) never change.
	}

	void Step()
	{

	}
};