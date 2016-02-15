

std::default_random_engine random;
Crypt crypt(80, 23, random, 108000);

void InitSimulation()
{
	unsigned time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	random.seed(time);
}

void StepSimulation()
{
	crypt.Step();
}

void CleanUpSimulation()
{
}