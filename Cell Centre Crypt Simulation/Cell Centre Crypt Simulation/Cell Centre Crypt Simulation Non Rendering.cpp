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

		while(framecount < totalFrames)
		{
			Simulation::StepSimulation();
			framecount++;

			if(framecount % 200 == 0)
			{
				outputFile << Simulation::crypt->Cellularity();
				outputFile << ",\n";
			}

			//Sleep(10);
		}

		outputFile.close();

		Simulation::CleanUpSimulation();
	}
	return 0;
}