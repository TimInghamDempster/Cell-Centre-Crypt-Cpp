
struct Cells
{
	int numCells;

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
};