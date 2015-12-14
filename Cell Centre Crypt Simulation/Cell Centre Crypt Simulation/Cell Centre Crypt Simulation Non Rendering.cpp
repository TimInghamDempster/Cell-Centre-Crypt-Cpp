
#include "SystemIncludes.cpp"

#include "ProgramIncludes.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 2000;

	InitialiseSimulation();
	
	while(framecount < totalFrames)
	{
		StepSimulation();
		framecount++;
	}

	CleanUpSimulation();

	return 0;
}