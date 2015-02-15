#include "soundmanager.h"
#include "preferences.h"

SoundManager* SoundManager::m_instance = NULL;

SoundManager::SoundManager()
	:m_isLoaded(false),m_time(0)
{
}

void SoundManager::LoadRessources()
{
	m_dirtWalking.LoadFromFile(SOUND_PATH"dirt_walk.wav");
	m_breakCube.LoadFromFile(SOUND_PATH "break.wav");
	m_glassBreaking.LoadFromFile(SOUND_PATH"glass.wav");
	m_jump.LoadFromFile(SOUND_PATH "jump.wav");
	m_hurt.LoadFromFile(SOUND_PATH "player_hurt.wav");
	m_die.LoadFromFile(SOUND_PATH "player_die.wav");
	m_skinnyShout.LoadFromFile(SOUND_PATH "skinny_shout.wav");
	m_skinnyHurt.LoadFromFile(SOUND_PATH  "skinny_hurt.wav");
	m_skinnyDie.LoadFromFile(SOUND_PATH "skinny_die.wav");
	m_fatsoShout.LoadFromFile(SOUND_PATH "fatso_shout.wav");
	m_fatsoHurt.LoadFromFile(SOUND_PATH "fatso_hurt.wav");
	m_fatsoDie.LoadFromFile(SOUND_PATH "fatso_die.wav");
	m_piggyShout.LoadFromFile(SOUND_PATH "piggy_shout.wav");
	m_piggyHurt.LoadFromFile(SOUND_PATH "piggy_hurt.wav");
	m_piggyDie.LoadFromFile(SOUND_PATH "piggy_die.wav");
	m_flyMode.LoadFromFile(SOUND_PATH "aaaaaaieeeeee.wav")	;

	m_musicUnderground.OpenFromFile(MUSIC_PATH "Underground.ogg");
	m_musicOverworld.OpenFromFile(MUSIC_PATH "Overworld.ogg");
	m_musicAmbiance.OpenFromFile(MUSIC_PATH "ambiance.ogg");

	m_musicList.push_back(&m_musicAmbiance);
	m_musicList.push_back(&m_musicOverworld);
	m_musicList.push_back(&m_musicUnderground);


	m_isLoaded = true;
}


SoundManager* SoundManager::GetInstance()
{
	if(m_instance == 0)
		m_instance = new SoundManager();

	return m_instance;

}

void SoundManager::StartMusic()
 {
	 m_indexMusic =0;

	 for (int i = 0;i< m_musicList.size();++i)
	 {
		 m_musicList[i]->Stop();
	 }

	 m_musicList[m_indexMusic]->Play();

 }

void SoundManager::StopMusic()
{
	 for (int i = 0; i < m_musicList.size(); ++i)
	 {
		 m_musicList[i]->Stop();
	 }


}

void SoundManager::StartSound(SOUND_EVENT sound)
{
	sf::Sound* temp;
	switch(sound)
	{
		case DIRT_STEP:
			 temp = new sf::Sound(m_dirtWalking,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

		    case GLASS_BREAKING:
			 temp = new sf::Sound(m_glassBreaking,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case CUBE_BREAKING:
			 temp = new sf::Sound(m_breakCube,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case JUMP:
			 temp = new sf::Sound(m_jump,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case  HURT:
			 temp = new sf::Sound(m_hurt,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case DIE:
		 temp = new sf::Sound(m_die,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case FLY:
			 temp = new sf::Sound(m_flyMode,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case SKINNY_SHOUT:
			 temp = new sf::Sound(m_skinnyShout,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case SKINNY_HURT:
			temp = new sf::Sound(m_skinnyHurt,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case SKINNY_DIE:
			 temp = new sf::Sound(m_skinnyDie,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case FATSO_SHOUT:
			 temp = new sf::Sound(m_fatsoShout,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case FATSO_HURT:
			 temp = new sf::Sound(m_fatsoHurt,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case FATSO_DIE:
			 temp = new sf::Sound(m_fatsoDie,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case PIGGY_SHOUT:
			 temp = new sf::Sound(m_piggyShout,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case PIGGY_HURT:
			 temp = new sf::Sound(m_piggyHurt,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;

			case PIGGY_DIE:
			 temp = new sf::Sound(m_piggyDie,false,1.f,Preferences::GetSoundVolume()*100);
			temp->Play();
			m_soundBoard.push_back(temp);
			break;
	}
}

void SoundManager::Update(float elapsedTime)
{
	if(m_musicList[m_indexMusic]->GetStatus() == m_musicList[m_indexMusic]->Stopped)
	{
		m_indexMusic++;
		if (m_indexMusic >= m_musicList.size())
		{
			m_indexMusic =0;
		}
		m_musicList[m_indexMusic]->Play();
	}
	m_time += elapsedTime;
	if(m_time >= 2.f )	
	{
		m_time =0;
		CleanUp();
	}
}
void SoundManager::SetVolumeMusic(float volume)
{
	for (int i = 0;i< m_musicList.size();++i)
	 {
		 m_musicList[i]->SetVolume(volume*100);
	 }
}

void SoundManager::SetVolumeSound(float volume)
{

	
	for (int i =0;i<m_soundBoard.size();++i)
	{
		m_soundBoard[i]->SetVolume(volume*100);
	}
}

void SoundManager::CleanUp()
{
	for (int i =0;i<m_soundBoard.size();++i)
	{
		if(m_soundBoard[i]->GetStatus() == m_soundBoard[i]->Stopped)
		{
			delete m_soundBoard[i];
			m_soundBoard.erase(m_soundBoard.begin()+i);
		}
	}
	
}

SoundManager:: ~SoundManager()
{
	//TODO: Décommenter
	/*for (int i = 0;i < m_musicList.size(); ++i)
	{
		delete m_musicList[i];
	}*/

	for (int i = 0;i < m_soundBoard.size(); ++i)
	{
		delete m_soundBoard[i];
	}
}