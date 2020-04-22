#pragma once

// 무조건 랜덤을 하고 싶으면 SeedRandomUInt()을 먼저 선언
// 그렇지 않으면 고정 시드
// 시드를 직접 입력하고 싶으면 SetSeed
class RandomNumber
{
public:
	static void Init();
	static unsigned int SeedRandomUInt();
	static unsigned int TimeRandomUInt();
	static void SetSeed(unsigned int seed);
	static int GetRandomNumber(int min, int max);

private:
	RandomNumber() {}
	~RandomNumber() {}

private:
	static int mSeed;
	static int mTimeSeed;

};