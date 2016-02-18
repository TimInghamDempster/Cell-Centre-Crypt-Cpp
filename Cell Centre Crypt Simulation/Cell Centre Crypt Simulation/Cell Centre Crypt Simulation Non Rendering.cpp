#include "SystemIncludes.cpp"

#include "ProgramIncludes.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 1000000;
	
	InitSimulation();
	
	std::ofstream outputFile;
	outputFile.open("testData.csv");

	while(framecount < totalFrames)
	{
		StepSimulation();
		framecount++;

		if(framecount % 200 == 0)
		{
			outputFile << crypt.Cellularity();
			outputFile << ",\n";
		}

		//Sleep(10);
	}

	outputFile.close();
	
	CleanUpSimulation();

	return 0;
}