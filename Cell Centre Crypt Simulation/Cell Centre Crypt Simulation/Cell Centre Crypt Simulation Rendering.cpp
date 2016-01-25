
#include "SystemIncludes.cpp"

#include "WindowsPlatform.cpp"

#include "ProgramIncludes.cpp"

#include "../D3D/D3DIncludes.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 50000000;

	HINSTANCE hInst = GetModuleHandle(NULL);
	HWND hwnd = TCreateWindow(hInst);
	Renderer::Init(hwnd, 1280, 720);
	
	while(framecount < totalFrames)
	{
		TWinMain();
		StepSimulation();
		Renderer::Draw();
		framecount++;
	}

	CleanUpSimulation();
	Renderer::CleanUp();

	return 0;
}