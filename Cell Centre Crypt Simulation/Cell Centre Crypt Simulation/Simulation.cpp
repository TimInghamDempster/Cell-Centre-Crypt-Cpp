
namespace Simulation
{
	struct SimSetup
	{
		double averageGrowthTimeInSeconds;
		double membraneAttachmentForce;
		std::string filename;
		MutationData mutationData;
	};

	std::vector<Crypt*> crypts;
	std::string filename;
	SimSetup currentSettings;
	double mutationHeight = -100.0;
	NormalDistributionRNG* normalRNG;

	bool InitSimulation()
	{

		MutationData noMutation = { false, false, false };
		MutationData g0Mutation = { true, false, false };
		MutationData adhesionMutation = {false, true, false };
		MutationData cellForceMutation = {false, false, true };
		MutationData mutateAPC = { true, true, true };

		SimSetup settings[] = 
		{
			{108000,0.001, "data/30hrCC_001af_run1.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run2.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run3.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run4.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run5.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run6.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run7.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run8.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run9.csv", noMutation},
			{108000,0.001, "data/30hrCC_001af_run10.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run1.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run2.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run3.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run4.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run5.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run6.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run7.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run8.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run9.csv", noMutation},
			{72000,0.001, "data/20hrCC_001af_run10.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run1.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run2.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run3.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run4.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run5.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run6.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run7.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run8.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run9.csv", noMutation},
			{90000,0.001, "data/25hrCC_001af_run10.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run1.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run2.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run3.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run4.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run5.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run6.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run7.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run8.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run9.csv", noMutation},
			{126000,0.001, "data/35hrCC_001af_run10.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run1.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run2.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run3.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run4.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run5.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run6.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run7.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run8.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run9.csv", noMutation},
			{144000,0.001, "data/40hrCC_001af_run10.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run1.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run2.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run3.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run4.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run5.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run6.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run7.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run8.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run9.csv", noMutation},
			{108000,0.01, "data/30hrCC_01af_run10.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run1.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run2.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run3.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run4.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run5.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run6.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run7.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run8.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run9.csv", noMutation},
			{108000,0.0001, "data/30hrCC_0001af_run10.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run1.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run2.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run3.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run4.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run5.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run6.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run7.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run8.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run9.csv", noMutation},
			{108000,0.005, "data/30hrCC_005af_run10.csv", noMutation},
			{108000,0.001, "data/mutate_quiesence_run1.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run2.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run3.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run4.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run5.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run6.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run7.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run8.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run9.csv", g0Mutation},
			{108000,0.001, "data/mutate_quiesence_run10.csv", g0Mutation},
			{108000,0.001, "data/mutate_adhesion_run1.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run2.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run3.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run4.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run5.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run6.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run7.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run8.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run9.csv", adhesionMutation},
			{108000,0.001, "data/mutate_adhesion_run10.csv", adhesionMutation},
			{108000,0.001, "data/mutate_cell_force_run1.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run2.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run3.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run4.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run5.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run6.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run7.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run8.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run9.csv", cellForceMutation},
			{108000,0.001, "data/mutate_cell_force_run10.csv", cellForceMutation},
			{108000,0.001, "data/mutate_APC_run1.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run2.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run3.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run4.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run5.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run6.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run7.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run8.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC_run9.csv", mutateAPC},
			{108000,0.001, "data/mutate_APC__run10.csv", mutateAPC},
		};

		unsigned numSettings = 120;

		char* env = getenv("SGE_TASK_ID");

		std::stringstream stream;
	
		int seed = time(NULL);
		if(env)
		{
			unsigned taskId = 0;

			stream << env;
			stream >> taskId;

			if(taskId < numSettings)
			{
				// time() resolution is really poor so need to make sure that repeats don't have the same seed.
				seed += taskId;

				currentSettings = settings[taskId];
				
				double cellCycleTime = settings[taskId].averageGrowthTimeInSeconds;
				double attachmentForce = settings[taskId].membraneAttachmentForce;
				filename = settings[taskId].filename;

				double secondsPerTimestep = 30.0;
				normalRNG = new NormalDistributionRNG(cellCycleTime / secondsPerTimestep, 2.625 * 3600.0 / secondsPerTimestep);
				crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, normalRNG, Vector3D(-2000.0f,0.0f,0.0f)));
				
				crypts.push_back(new Crypt(80, 23, cellCycleTime, attachmentForce, normalRNG, Vector3D(2000.0f,0.0f,0.0f)));

				srand(seed);
				return true;
			}
		}

		return false;
	}

	void DoMutation()
	{
		float minDelta = 100000.0; // Sufficiently big number, ie bigger than a crypt
		CellBox* closestBox = NULL;
		int closestCell = 0;

		for(int col = 0; col < (int)crypts[0]->m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = Simulation::crypts[0]->m_grid.m_columns[col];
			for(int row = 0; row < (int)column.size(); row++)
			{
				CellBox& box = column[row];
				for(int cell = 0; cell < box.m_positions.size(); cell++)
				{
					Vector3D& vec = box.m_positions[cell];
					float delta = fabs((vec.y + crypts[0]->m_cryptHeight) - mutationHeight);

					if(delta < minDelta && vec.z > 300.0)
					{
						minDelta = delta;
						closestBox = &box;
						closestCell = cell;
					}
				}
			}
		}

		closestBox->m_mutations[closestCell] = currentSettings.mutationData;
	}

	void StepSimulation()
	{
		for(int i = 0; i< Simulation::crypts.size(); i++)
		{
			crypts[i]->Step();
		}
	}

	void CleanUpSimulation()
	{
		delete normalRNG;
		for(int i = 0; i < crypts.size(); i++)
		{
			delete crypts[i];
		}
	}
}
