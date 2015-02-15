//======================================================================
//Auteur : J-F Goyer
//Date de création : 23 février 2012
//Description : Gère les sons et la musique. Implémente le Singleton
//======================================================================
#ifndef SOUND_MANAGER_H__
#define SOUND_MANAGER_H__

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "define.h"

class SoundManager
{
private:
	sf::SoundBuffer m_dirtWalking;
	sf::SoundBuffer m_breakCube;
	sf::SoundBuffer m_glassBreaking;
	sf::SoundBuffer m_jump;
	sf::SoundBuffer m_hurt;
	sf::SoundBuffer m_die;
    sf::SoundBuffer m_skinnyShout;
	sf::SoundBuffer m_skinnyHurt;
	sf::SoundBuffer m_skinnyDie;
	sf::SoundBuffer m_fatsoShout;
	sf::SoundBuffer m_fatsoHurt;
	sf::SoundBuffer m_fatsoDie;
	sf::SoundBuffer m_piggyShout;
	sf::SoundBuffer m_piggyHurt;
	sf::SoundBuffer m_piggyDie;
	sf::SoundBuffer m_flyMode;

	sf::Music m_musicUnderground;
	sf::Music m_musicOverworld;
	sf::Music m_musicAmbiance;
	std::vector<sf::Sound*> m_soundBoard;
	std::vector<sf::Music*> m_musicList;
	float m_time;
	int m_indexMusic;	
	bool m_isLoaded;
	static SoundManager* m_instance;
	void CleanUp();
	SoundManager();
	
public:
	~SoundManager();

	enum SOUND_EVENT
	{
	DIRT_STEP,GLASS_BREAKING,CUBE_BREAKING,JUMP,HURT,DIE,FLY,SKINNY_SHOUT,SKINNY_HURT,SKINNY_DIE,FATSO_SHOUT
	,FATSO_HURT, FATSO_DIE,PIGGY_SHOUT,PIGGY_HURT,PIGGY_DIE};

	void LoadRessources();
	void StartMusic();
	void StopMusic();
	void StartSound(SOUND_EVENT sound);
	void Update(float elapsedTime);
	void SetVolumeSound(float volume);
	void SetVolumeMusic(float volume);
	static SoundManager* GetInstance();

};
#endif
