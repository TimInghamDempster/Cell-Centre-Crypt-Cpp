#include "SystemIncludes.cpp"

#include "ProgramIncludes.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 1000000;
	
	bool init = Simulation::InitSimulation();
	
	if(init)
	{
		std::ofstream outputFile;
		outputFile.open(Simulation::filename);

		outputFile << "cellularity, anoikis, divisions, stem count, stem count in cycle, proliferation count, proliferation count in cycle";
		outputFile << ",\n";

		while(framecount < totalFrames)
		{
			Simulation::StepSimulation();
			framecount++;

			if(framecount % 200 == 0)
			{
				int cellularity = 0;
				int stemCount = 0;
				int stemInCycleCount = 0;
				int proliferatingCount = 0;
				int proliferatingInCycleCount = 0;

				Simulation::crypt->GetCounts(cellularity, stemCount, stemInCycleCount, proliferatingCount, proliferatingInCycleCount);

				outputFile << cellularity;
				outputFile << ',';
				outputFile << Simulation::crypt->m_numAnoikisEvents;
				outputFile << ',';
				outputFile << Simulation::crypt->m_numBirthEvents;
				outputFile << ',';
				outputFile << stemCount;
				outputFile << ',';
				outputFile << stemInCycleCount;
				outputFile << ',';
				outputFile << proliferatingCount;
				outputFile << ',';
				outputFile << proliferatingInCycleCount;
				outputFile << ",\n";
				Simulation::crypt->ClearCounters();
			}

			//Sleep(10);
		}

		outputFile.close();

		Simulation::CleanUpSimulation();
	}
	return 0;
}