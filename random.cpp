/*
 * Random.cpp
 *
 *  Created on: Feb 15, 2012
 *      Author: j-r
 */

#include "random.h"

Random* Random::m_instance = 0;

int Random::GetNext() {
	m_firstSeed = 36969 * (m_firstSeed & 65535) + (m_firstSeed >> 16);
	m_secondSeed = 18000 * (m_secondSeed & 65535) + (m_secondSeed >> 16);
    return abs((m_firstSeed << 16) + m_secondSeed);  /* 32-bit result */
}

int Random::GetNext(int max) {
	return GetNext() % max;
}

int Random::GetNextAt(int x, int y) {
	x += 543654;
	y += 657643;
	
	int fSeed = 36969 * (m_firstSeed + x & 65535) + (m_firstSeed + x >> 16);
	int sSeed = 18000 * (m_secondSeed + y & 65535) + (m_secondSeed + y >> 16);

	Random rnd(abs((fSeed << 16) + sSeed));
	return rnd.GetNext();
}

int Random::GetNextAt(int x, int y, int max) {
	int v = GetNextAt(x, y) % max;
	return v;
}


Random::Random() {
	SetSeed(WORLD_SEED);
}
Random::Random(int seed) {
	SetSeed(seed);
}
Random::Random(int seed, int secondSeed) {
	SetSeed(seed, secondSeed);
}

Random* Random::GetInstance() {
	if(m_instance == 0) {
		m_instance = new Random(WORLD_SEED);
	}
	return m_instance;
}

void Random::SetSeed(int seed) {
	seed *= 52456;

	SetSeed(seed << 16, seed >> 16);
}

void Random::SetSeed(int seed, int secondSeed) {
	m_initialFirstSeed = m_firstSeed = (seed * -21351);
	m_initialSecondSeed = m_firstSeed = (secondSeed * -6875);
}

float Random::GetNextFloat(float min, float max)
{
	float value = GetNext((max-min)*10);
	return (value / 10)+ min;
}
