

std::default_random_engine random;
Crypt crypt(80, 23, random, 108000);

void StepSimulation()
{
	crypt.Step();
}

void CleanUpSimulation()
{
}