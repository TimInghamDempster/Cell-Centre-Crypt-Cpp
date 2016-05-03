
namespace Simulation
{
	struct SimSetup
	{
		double averageGrowthTimeInSeconds;
		double membraneAttachmentForce;
		std::string filename;
		double mutationHeight;
	};

	std::default_random_engine myRandom;
	Crypt* crypt;
	std::string filename;
	SimSetup currentSettings;

	bool InitSimulation()
	{
		SimSetup settings[] = 
		{
			{108000,0.001, "data/30hrCC_001af_run1.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run2.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run3.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run4.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run5.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run6.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run7.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run8.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run9.csv", 300},
			{108000,0.001, "data/30hrCC_001af_run10.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run1.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run2.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run3.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run4.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run5.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run6.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run7.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run8.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run9.csv", 300},
			{72000,0.001, "data/20hrCC_001af_run10.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run1.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run2.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run3.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run4.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run5.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run6.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run7.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run8.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run9.csv", 300},
			{90000,0.001, "data/25hrCC_001af_run10.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run1.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run2.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run3.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run4.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run5.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run6.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run7.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run8.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run9.csv", 300},
			{126000,0.001, "data/35hrCC_001af_run10.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run1.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run2.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run3.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run4.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run5.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run6.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run7.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run8.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run9.csv", 300},
			{144000,0.001, "data/40hrCC_001af_run10.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run1.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run2.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run3.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run4.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run5.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run6.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run7.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run8.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run9.csv", 300},
			{108000,0.01, "data/30hrCC_01af_run10.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run1.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run2.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run3.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run4.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run5.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run6.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run7.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run8.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run9.csv", 300},
			{108000,0.0001, "data/30hrCC_0001af_run10.csv", 300}
		};

		unsigned numSettings = 70;

		char* env = getenv("SGE_TASK_ID");

		std::stringstream stream;
	
		if(env)
		{
			unsigned taskId = 0;

			stream << env;
			stream >> taskId;

			if(taskId < numSettings)
			{
				
				currentSettings = settings[taskId];
				
				double cellCycleTime = settings[taskId].averageGrowthTimeInSeconds;
				double attachmentForce = settings[taskId].membraneAttachmentForce;
				filename = settings[taskId].filename;

				crypt = new Crypt(80, 23, myRandom, cellCycleTime, attachmentForce);

				unsigned time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
				myRandom.seed(time);
				return true;
			}
		}

		return false;
	}

	void DoMutation()
	{
		float minDelta = 100000.0; // Sufficiently big number, ie bigger than a crypt
		CellBox* closestBox = nullptr;
		int closestCell = 0;

		for(int col = 0; col < (int)crypt->m_grid.m_columns.size(); col++)
		{
			std::vector<CellBox>& column = Simulation::crypt->m_grid.m_columns[col];
			for(int row = 0; row < (int)column.size(); row++)
			{
				CellBox& box = column[row];
				for(int cell = 0; cell < box.m_positions.size(); cell++)
				{
					Vector3D& vec = box.m_positions[cell];
					float delta = std::fabs((vec.y + crypt->m_cryptHeight) - currentSettings.mutationHeight);

					if(delta < minDelta && vec.z > 300.0)
					{
						minDelta = delta;
						closestBox = &box;
						closestCell = cell;
					}
				}
			}
		}

		closestBox->m_attachmentStrengths[closestCell] *= 1.0;
	}

	void StepSimulation()
	{
		crypt->Step();
	}

	void CleanUpSimulation()
	{
		delete crypt;
	}
}