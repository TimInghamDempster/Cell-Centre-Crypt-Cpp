
#include "SystemIncludes.cpp"

#include "ProgramIncludes.cpp"

#include "../D3D/D3DIncludes.cpp"

int main(int argc, char* argv[])
{
	int framecount = 0;
	const int totalFrames = 1000000;
	const int mutationFrame = 1000;

	HINSTANCE hInst = GetModuleHandle(NULL);
	HWND hwnd = TCreateWindow(hInst);
	Renderer::Init(hwnd, 1280, 720);
	bool init = Simulation::InitSimulation();
	
	if(init)
	{
		std::ofstream outputFile;
		outputFile.open("C:/Users/Tim/Desktop/testData.csv");

		outputFile << "cellularity, anoikis, divisions, stem count, stem count in cycle, proliferation count, proliferation count in cycle";
		outputFile << ",\n";

		while(framecount < totalFrames)
		{
			TWinMain();
			Simulation::StepSimulation();
			Renderer::Draw();
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
	
		outputFile << "\n Anoikis Locations \n";

		for(int i = 0; i < 100; i++)
		{
			outputFile << Simulation::crypt->m_anoikisHeights[i];
			outputFile << ",\n";
		}

		outputFile.close();
	
		Simulation::CleanUpSimulation();
	}
	Renderer::CleanUp();	

	return 0;
}