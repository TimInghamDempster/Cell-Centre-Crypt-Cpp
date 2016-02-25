
namespace Simulation
{
	std::default_random_engine myRandom;
	Crypt* crypt;
	std::string filename;

	struct SimSetup
	{
		double averageGrowthTimeInSeconds;
		double membraneAttachmentForce;
		std::string filename;
	};

	bool InitSimulation()
	{
		SimSetup settings[] = 
		{
			{108000,0.001, "data/30hrCC_001af_run1.csv"},
			{108000,0.001, "data/30hrCC_001af_run2.csv"},
			{108000,0.001, "data/30hrCC_001af_run3.csv"},
			{108000,0.001, "data/30hrCC_001af_run4.csv"},
			{108000,0.001, "data/30hrCC_001af_run5.csv"},
			{108000,0.001, "data/30hrCC_001af_run6.csv"},
			{108000,0.001, "data/30hrCC_001af_run7.csv"},
			{108000,0.001, "data/30hrCC_001af_run8.csv"},
			{108000,0.001, "data/30hrCC_001af_run9.csv"},
			{108000,0.001, "data/30hrCC_001af_run10.csv"},
			{72000,0.001, "data/20hrCC_001af_run1.csv"},
			{72000,0.001, "data/20hrCC_001af_run2.csv"},
			{72000,0.001, "data/20hrCC_001af_run3.csv"},
			{72000,0.001, "data/20hrCC_001af_run4.csv"},
			{72000,0.001, "data/20hrCC_001af_run5.csv"},
			{72000,0.001, "data/20hrCC_001af_run6.csv"},
			{72000,0.001, "data/20hrCC_001af_run7.csv"},
			{72000,0.001, "data/20hrCC_001af_run8.csv"},
			{72000,0.001, "data/20hrCC_001af_run9.csv"},
			{72000,0.001, "data/20hrCC_001af_run10.csv"},
			{90000,0.001, "data/25hrCC_001af_run1.csv"},
			{90000,0.001, "data/25hrCC_001af_run2.csv"},
			{90000,0.001, "data/25hrCC_001af_run3.csv"},
			{90000,0.001, "data/25hrCC_001af_run4.csv"},
			{90000,0.001, "data/25hrCC_001af_run5.csv"},
			{90000,0.001, "data/25hrCC_001af_run6.csv"},
			{90000,0.001, "data/25hrCC_001af_run7.csv"},
			{90000,0.001, "data/25hrCC_001af_run8.csv"},
			{90000,0.001, "data/25hrCC_001af_run9.csv"},
			{90000,0.001, "data/25hrCC_001af_run10.csv"},
			{126000,0.001, "data/35hrCC_001af_run1.csv"},
			{126000,0.001, "data/35hrCC_001af_run2.csv"},
			{126000,0.001, "data/35hrCC_001af_run3.csv"},
			{126000,0.001, "data/35hrCC_001af_run4.csv"},
			{126000,0.001, "data/35hrCC_001af_run5.csv"},
			{126000,0.001, "data/35hrCC_001af_run6.csv"},
			{126000,0.001, "data/35hrCC_001af_run7.csv"},
			{126000,0.001, "data/35hrCC_001af_run8.csv"},
			{126000,0.001, "data/35hrCC_001af_run9.csv"},
			{126000,0.001, "data/35hrCC_001af_run10.csv"},
			{144000,0.001, "data/40hrCC_001af_run1.csv"},
			{144000,0.001, "data/40hrCC_001af_run2.csv"},
			{144000,0.001, "data/40hrCC_001af_run3.csv"},
			{144000,0.001, "data/40hrCC_001af_run4.csv"},
			{144000,0.001, "data/40hrCC_001af_run5.csv"},
			{144000,0.001, "data/40hrCC_001af_run6.csv"},
			{144000,0.001, "data/40hrCC_001af_run7.csv"},
			{144000,0.001, "data/40hrCC_001af_run8.csv"},
			{144000,0.001, "data/40hrCC_001af_run9.csv"},
			{144000,0.001, "data/40hrCC_001af_run10.csv"},
			{108000,0.01, "data/30hrCC_01af_run1.csv"},
			{108000,0.01, "data/30hrCC_01af_run2.csv"},
			{108000,0.01, "data/30hrCC_01af_run3.csv"},
			{108000,0.01, "data/30hrCC_01af_run4.csv"},
			{108000,0.01, "data/30hrCC_01af_run5.csv"},
			{108000,0.01, "data/30hrCC_01af_run6.csv"},
			{108000,0.01, "data/30hrCC_01af_run7.csv"},
			{108000,0.01, "data/30hrCC_01af_run8.csv"},
			{108000,0.01, "data/30hrCC_01af_run9.csv"},
			{108000,0.01, "data/30hrCC_01af_run10.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run1.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run2.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run3.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run4.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run5.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run6.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run7.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run8.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run9.csv"},
			{108000,0.0001, "data/30hrCC_0001af_run10.csv"}
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

	void StepSimulation()
	{
		crypt->Step();
	}

	void CleanUpSimulation()
	{
		delete crypt;
	}
}