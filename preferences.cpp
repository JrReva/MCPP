#include "preferences.h"
#include "engine.h"
#include"soundmanager.h"

float Preferences::m_musicVolume = 1.f;
float Preferences::m_soundVolume = 1.f;
int Preferences::m_loadDistance = 128;
float Preferences::m_fogDensity = 0.02f;

float Preferences::GetFogAirDensity()
{
	return m_fogDensity; 
}

float Preferences::GetFogWaterDensity()
{
	return m_fogDensity*2;
}

int Preferences::GetViewDistance() {
	return m_loadDistance * 0.75;
}

int Preferences::GetLoadDistance() {
	return m_loadDistance;
}

int Preferences::GetMobRenderDistance() {
	return GetViewDistance() * 0.9f;
}

int Preferences::GetMobDisposeDistance() {
	return GetLoadDistance() * 0.8f;
}

float Preferences::GetMusicVolume() {
	return m_musicVolume;
}

float Preferences::GetSoundVolume() {
	return m_soundVolume;
}

void Preferences::SetMusicVolume(float volume) {
	m_musicVolume = volume;
	SoundManager::GetInstance()->SetVolumeMusic(volume);
}

void Preferences::SetSoundVolume(float volume) {
	m_soundVolume = volume;
	SoundManager::GetInstance()->SetVolumeSound(volume);
}

void Preferences::SetLoadDistance(int value) {
	m_loadDistance = value;
	Engine::GetInstance()->OnViewDistanceChanged();
}

int Preferences::GetMaxMob()
{
	//TODO : Agencer à la difficulté
	return 10;
}

float Preferences::GetMobSpawnTime()
{
	//TODO : Agencer à la difficulté
	return 30;
}

MobType Preferences::GetMobType(int proba)
{
	//TODO : Agencer à la difficulté et/ou au temps de la journée.
	if(proba < 50)
		return PIGGY;
	else if(proba < 75)
		return SKINNY;
	else
		return FATSO;
}

void Preferences::SetFogDensity(float value)
{
	Preferences::m_fogDensity = value;
}