
struct Cells
{
	int upperBound;
	int lowerBound;

	int upperMemoryBound;

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

	int newCellCount;
	int* newCells;

	CylindricalGrid* grid;

	void UpdateCell(int cellPositionInArrays)
	{
	}

	void InsertNewCells()
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

	void MoveBoxDownY(int cellToMove)
	{
		FenceId fenceBelowCellToMove = grid->FindFenceAbove(positionsX[cellToMove], positionsY[cellToMove], positionsZ[cellToMove]);
		fenceBelowCellToMove.row--;
		int bottomCell = grid->GetFenceIndex(fenceBelowCellToMove) + 1;

		SwapCells(cellToMove, bottomCell); // Put the cell at the bottom of it's box
		grid->IncrementFenceIndex(fenceBelowCellToMove); // Move the box boundary up one so bottom cell of box above is now in this box
	}

	void MoveBoxUpY(int cellToMove)
	{
		FenceId fenceAboveCellToMove = grid->FindFenceAbove(positionsX[cellToMove], positionsY[cellToMove], positionsZ[cellToMove]);
		int topCell = grid->GetFenceIndex(fenceAboveCellToMove);

		SwapCells(cellToMove, topCell); // Put the cell at the top of it's box
		grid->DecrementFenceIndex(fenceAboveCellToMove); // Move the box boundary down one so top cell is now in the box above
	}

	void SwapCells(int cell1, int cell2)
	{
		float tempX = positionsX[cell1];
		positionsX[cell1] = positionsX[cell2];
		positionsX[cell2] = tempX;
		float tempY = positionsY[cell1];
		positionsY[cell1] = positionsY[cell2];
		positionsY[cell2] = tempY;
		float tempZ = positionsZ[cell1];
		positionsZ[cell1] = positionsZ[cell2];
		positionsZ[cell2] = tempZ;
		
		float tempMembraneX = onMembranePositionsX[cell1];
		onMembranePositionsX[cell1] = onMembranePositionsX[cell2];
		onMembranePositionsX[cell2] = tempMembraneX;
		float tempMembraneY = onMembranePositionsY[cell1];
		onMembranePositionsY[cell1] = onMembranePositionsY[cell2];
		onMembranePositionsY[cell2] = tempMembraneY;
		float tempMembraneZ = onMembranePositionsZ[cell1];
		onMembranePositionsZ[cell1] = onMembranePositionsZ[cell2];
		onMembranePositionsZ[cell2] = tempMembraneZ;

		float tempR = radii[cell1];
		radii[cell1] = radii[cell2];
		radii[cell2] = tempR;

		int tempStageTimestep = currentStageNumTimesteps[cell1];
		currentStageNumTimesteps[cell1] = currentStageNumTimesteps[cell2];
		currentStageNumTimesteps[cell2] = tempStageTimestep;

		int tempGrowthTimestep = growthStageRequiredTimesteps[cell1];
		growthStageRequiredTimesteps[cell1] = growthStageRequiredTimesteps[cell2];
		growthStageRequiredTimesteps[cell2] = tempGrowthTimestep;

		int tempSubCell = otherSubCellIndex[cell1];
		otherSubCellIndex[cell1] = otherSubCellIndex[cell2];
		otherSubCellIndex[cell2] = tempSubCell;

		CellCycleStages::Stages tempStage = cycleStages[cell1];
		cycleStages[cell1] = cycleStages[cell2];
		cycleStages[cell2] = tempStage;
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
			int newLowerBound = upperMemoryBound - upperBound; // off by 1?

			for(int i = 0; i < upperBound; i++)
			{
				CopyCell(i, newLowerBound + i);
			}

			lowerBound = newLowerBound;
			upperBound = upperMemoryBound;
		}

		lowerBound--;
		positionsX[lowerBound] = onMembranePositionsX[lowerBound];
		positionsY[lowerBound] = onMembranePositionsY[lowerBound];
		positionsZ[lowerBound] = onMembranePositionsZ[lowerBound];
	}
};