
struct Cells
{
	int upperBound;
	int lowerBound;

	float* positionsX;
	float* positionsY;
	float* positionsZ;
	
	float* onMembranePositionsX;
	float* onMembranePositionsY;
	float* onMembranePositionsZ;

    float* radii;

	int* currentStageNumTimesteps;
	int* growthStageRequiredTimesteps;

	int* otherSubCellIndex;

	CellCycleStages::Stages* cycleStages;

	int deadCellCount;
	int* deadCells;

	void UpdateCell(int cellPositionInArrays)
	{
	}

	void RemoveDeadCells()
	{
		// Does removal and compaction in O(n)
		// Walk up from first dead cell copying cells above down to replace it
		// increase the distance copied at each new dead cell

		if(deadCellCount == 0)
		{
			return;
		}

		int currentDeadIndex = 1;
		
		for(int i = deadCells[0] + 1; i < upperBound; i++)
		{
			CopyCell(i, i - currentDeadIndex - 1); // Gets inlined, I checked the assembly.

			if(currentDeadIndex != deadCellCount && deadCells[currentDeadIndex] == i)
			{
				currentDeadIndex++;
			}
		}

		upperBound -= deadCellCount;

		deadCellCount = 0;
	}

	void CopyCell(int sourceIndex, int destIndex)
	{
		positionsX[destIndex] = positionsX[sourceIndex];
		positionsY[destIndex] = positionsY[sourceIndex];
		positionsZ[destIndex] = positionsZ[sourceIndex];
		
		onMembranePositionsX[destIndex] = onMembranePositionsX[sourceIndex];
		onMembranePositionsY[destIndex] = onMembranePositionsY[sourceIndex];
		onMembranePositionsZ[destIndex] = onMembranePositionsZ[sourceIndex];

		radii[destIndex] = radii[sourceIndex];

		currentStageNumTimesteps[destIndex] = currentStageNumTimesteps[sourceIndex];
		growthStageRequiredTimesteps[destIndex] = growthStageRequiredTimesteps[sourceIndex];

		otherSubCellIndex[destIndex] = otherSubCellIndex[sourceIndex];

		cycleStages[destIndex] = cycleStages[sourceIndex];
	}

	void AddNewCell()
	{
		if(lowerBound == 0)
		{
			//Memcpy the whole thing back to the top of the data segment and start again
			// don't return fail when this is implemented.  There are fail states but if
			// they occur the simulation has horribly broken anyway.
			return;
		}

		lowerBound--;
		positionsX[lowerBound] = onMembranePositionsX[lowerBound];
		positionsY[lowerBound] = onMembranePositionsY[lowerBound];
		positionsZ[lowerBound] = onMembranePositionsZ[lowerBound];
	}
};