

std::default_random_engine myRandom;
Crypt crypt(80, 23, myRandom, 108000);

void InitSimulation()
{
	unsigned time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	myRandom.seed(time);
}

void StepSimulation()
{
	crypt.Step();
}

void CleanUpSimulation()
{
}