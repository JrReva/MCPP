/*
 * preferences.h
 *
 *  Created on: Feb 22, 2012
 *      Author: j-r
 */

#ifndef PREFERENCES_H_
#define PREFERENCES_H_

#include "mobhandler.h"

class Preferences {
public:
	static int GetViewDistance();
	static void SetLoadDistance(int value);
	static void SetFogDensity(float value);

	static float GetFogWaterDensity();
	static float GetFogAirDensity();

	static int GetLoadDistance();
	static int GetMobDisposeDistance();
	static int GetMobRenderDistance();

	static float GetSoundVolume();
	static void SetSoundVolume(float volume);

	static float GetMusicVolume();
	static void SetMusicVolume(float volume);

	static int GetMaxMob();
	static float GetMobSpawnTime();
	static MobType GetMobType(int proba);

private:
	static int m_loadDistance;
	static float m_fogDensity;
	static float m_soundVolume;
	static float m_musicVolume;
};

#endif /* PREFERENCES_H_ */
