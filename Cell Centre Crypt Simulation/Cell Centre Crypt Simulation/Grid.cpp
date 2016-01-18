
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

	void CheckIntegrity()
	{
		for(int x = 0; x < m_numBoxesX; x++)
		{
			for(int z = 0; z < m_numBoxesZ; z++)
			{
				int bottomBox = GetBox(x, 0, z);
				int topBox = GetBox(x, m_numBoxesY - 1, z);
				
				int bottomIndex = m_boxBoundaryIndicesUpperBound[bottomBox];
				int topIndex = m_boxBoundaryIndicesUpperBound[topBox];

				if(topIndex < CalcArrayLength() - 1)
				{
					int nextColumnBottomIndex = m_boxBoundaryIndicesUpperBound[topBox + 1];

					if(nextColumnBottomIndex < topIndex && nextColumnBottomIndex > bottomIndex)
					{
						std::cerr << "Error: data structure collision.  See Grid.cpp CheckIntegrity()";
					}
				}
			}
		}
	}

	int CalcArrayLength()
	{
		return m_numBoxesX * m_numBoxesY * m_numBoxesZ;
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