
#include "SystemIncludes.cpp"

#include "WindowsPlatform.cpp"

#include "ProgramIncludes.cpp"

#include "../D3D/D3DIncludes.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 1000000;

	HINSTANCE hInst = GetModuleHandle(NULL);
	HWND hwnd = TCreateWindow(hInst);
	Renderer::Init(hwnd, 1280, 720);
	InitSimulation();
	
	std::ofstream outputFile;
	outputFile.open("C:/Users/Tim/Desktop/testData.csv");

	while(framecount < totalFrames)
	{
		TWinMain();
		StepSimulation();
		Renderer::Draw();
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
	Renderer::CleanUp();	

	return 0;
}