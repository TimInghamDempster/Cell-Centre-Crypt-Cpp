
#include "SystemIncludes.cpp"

#include "WindowsPlatform.cpp"

#include "ProgramIncludes.cpp"

#include "Renderer.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 50000000;

	InitialiseSimulation();
	InitRenderer();
	
	while(framecount < totalFrames)
	{
		StepSimulation();
		DrawScene();
		framecount++;
	}

	CleanUpSimulation();
	CleanUpRenderer();

	return 0;
}