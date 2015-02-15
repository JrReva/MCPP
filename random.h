#ifndef RANDOM_H__
#define RANDOM_H__
#include "define.h"

class Random {
private:
	int m_initialFirstSeed;
	int m_initialSecondSeed;

	int m_firstSeed;
	int m_secondSeed;
	static Random* m_instance;
public:
	Random();
	Random(int seed);
	Random(int seed, int secondSeed);

	static Random* GetInstance();

	int GetNext();
	int GetNext(int max);
	
	int GetNextAt(int x, int y);
	int GetNextAt(int x, int y, int max);

	float GetNextFloat(float min, float max);
	
	void SetSeed(int seed);
	void SetSeed(int seed, int secondSeed);
};

#endif
