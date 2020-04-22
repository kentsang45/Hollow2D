#include "RandomNumber.h"
#include <time.h>
#include <Windows.h>

int RandomNumber::mSeed = 0;
int RandomNumber::mTimeSeed = 0;

void RandomNumber::Init()
{
	srand((unsigned int)time(nullptr));
}

unsigned int RandomNumber::SeedRandomUInt()
{
	int randomNumber = 0;

	for (int i = 0; i < 32; i++)
	{
		randomNumber = randomNumber << 1;

		srand(mSeed++);
		int temp = rand() % 2;

		randomNumber = randomNumber | temp;
	}

	return randomNumber;
}

unsigned int RandomNumber::TimeRandomUInt()
{
	int randomNumber = 0;

	for (int i = 0; i < 32; i++)
	{
		randomNumber = randomNumber << 1;

		int temp = rand() % 2;

		randomNumber = randomNumber | temp;
	}

	return randomNumber;
}

void RandomNumber::SetSeed(unsigned int seed)
{
	mSeed = seed;
}

int RandomNumber::GetRandomNumber(int min, int max)
{
	if (max <= 0)
	{
		max = 1;
	}

	unsigned int seed = ++mSeed * 2;

	srand(seed);

	unsigned int random = SeedRandomUInt();

	random = random % max + min;

	return (int)random;
}
