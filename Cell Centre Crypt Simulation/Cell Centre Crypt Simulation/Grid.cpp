
struct Grid
{
	int* m_boxBoundaryIndicesUpperBound;

	int m_numBoxesX;
	int m_numBoxesY;
	int m_numBoxesZ;

	float m_boxSizeX;
	float m_boxSizeY;
	float m_boxSizeZ;
	
	float m_gridCentreInZeroSpaceX;
	float m_gridCentreInZeroSpaceY;
	float m_gridCentreInZeroSpaceZ;

	int FindBox(const float xPos, const float yPos, const float zPos) const
	{
		int x = CalcBoxOnAxis(xPos, m_gridCentreInZeroSpaceX, m_boxSizeX, m_numBoxesX);
		int y = CalcBoxOnAxis(yPos, m_gridCentreInZeroSpaceY, m_boxSizeY, m_numBoxesY);
		int z = CalcBoxOnAxis(zPos, m_gridCentreInZeroSpaceZ, m_boxSizeZ, m_numBoxesZ);

		return GetBox(x, y, z);
	}

	static int CalcBoxOnAxis(const float pos, const float gridCentreInZeroSpace, const float boxSize, const int boxCount)
	{
		int boxInInfiniteUniverse = (int)((pos + gridCentreInZeroSpace) / boxSize);
		int boxInHalfInfiniteUniverse = boxInInfiniteUniverse >= 0 ? boxInInfiniteUniverse : 0;
		int box = boxInHalfInfiniteUniverse < boxCount ? boxInHalfInfiniteUniverse : boxCount - 1;
		
		return box;
	}

	int GetBox(const int x, const int y, const int z) const
	{
		// Y has to be the contiguous direction. There is a
		// move fast-path in the contigusous direction and
		// most of our moves are in y
		return x * m_numBoxesY + y + z* m_numBoxesX * m_numBoxesY;
	}
};