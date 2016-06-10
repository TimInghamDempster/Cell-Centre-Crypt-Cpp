#include "SystemIncludes.cpp"

#include "ProgramIncludes.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 1000000;
	const int mutationFrame = 1000;
	
	bool init = Simulation::InitSimulation();
	
	if(init)
	{
		std::ofstream outputFile;
		outputFile.open(Simulation::filename.c_str());

		outputFile << "cellularity, anoikis, divisions, stem count, stem count in cycle, proliferation count, proliferation count in cycle, mutated cell count in flat mucosa, normal cell count in flat mucosa, mutated cell count in crypt, normal cell count in crypt";
		outputFile << ",\n";

		while(framecount < totalFrames)
		{
			Simulation::StepSimulation();
			framecount++;

			if(framecount == mutationFrame)
			{
				Simulation::DoMutation();
			}

			if(framecount % 200 == 0)
			{
				int cellularity = 0;
				int stemCount = 0;
				int stemInCycleCount = 0;
				int proliferatingCount = 0;
				int proliferatingInCycleCount = 0;
				int mutatedFlatMucosaCount = 0;
				int normalFlatMucosaCount = 0;
				int mutatedCryptCount = 0;
				int normalCryptCount = 0;

				Simulation::crypt->GetCounts(cellularity, stemCount, stemInCycleCount, proliferatingCount, proliferatingInCycleCount, mutatedFlatMucosaCount, normalFlatMucosaCount, mutatedCryptCount, normalCryptCount);

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
				outputFile << ",";
				outputFile << mutatedFlatMucosaCount;
				outputFile << ",";
				outputFile << normalFlatMucosaCount;
				outputFile << ",";
				outputFile << mutatedCryptCount;
				outputFile << ",";
				outputFile << normalCryptCount;
				outputFile << ",\n";
				Simulation::crypt->ClearCounters();
			}

			//Sleep(10);
		}

		outputFile << "\n Anoikis Locations \n";

		for(int i = 0; i < 100; i++)
		{
			outputFile << Simulation::crypt->m_anoikisHeights[i];
			outputFile << ",\n";
		}

		outputFile.close();

		Simulation::CleanUpSimulation();
	}
	return 0;
}
