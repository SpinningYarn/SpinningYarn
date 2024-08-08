#include "SoundManager.h"

SoundManager::SoundManager()
	:playCheck(false)
{
}

SoundManager::~SoundManager()
{
	system->close();
	system->release();
}

//SoundManager& SoundManager::GetInstance()
//{
//	static SoundManager instance;
//	return instance;
//}
SoundManager& SoundManager::GetInstance()
{
	static SoundManager* instance = new SoundManager();
	return *instance;
}


void SoundManager::SystemInitialize()
{
	FMOD::System_Create(&system);
	system->init(1000, FMOD_INIT_NORMAL, nullptr);
}

void SoundManager::CreateSound(const char* soundFile, eSound soundNum, bool isLoop)
{
	if (isLoop == true)
	{
		system->createSound(soundFile, FMOD_LOOP_NORMAL, 0, &effectSound[soundNum]);
	}
	else if (isLoop == false)
	{
		system->createSound(soundFile, FMOD_LOOP_OFF, 0, &effectSound[soundNum]);
	}
}

void SoundManager::CreateBGM(const char* soundFile, bgmSound bgmNum, bool isLoop)
{
	system->createSound(soundFile, FMOD_LOOP_NORMAL, 0, &BgmSound[bgmNum]);
}

void SoundManager::StopSound(eSound soundNum)
{
	effectSoundChannel[soundNum]->stop();
}

void SoundManager::StopBGM(bgmSound bgmNum)
{
	bgmSoundChannel[bgmNum]->stop();

}

void SoundManager::Finalize()
{

	//sound[32]->release();

	//soundChannel[SoundCount]->stop();
	//sound[SoundCount]->release();
	//system->close();
	//system->release();
}

void SoundManager::SoundUpdate()
{
	system->update();
}

void SoundManager::PlaySounds(eSound soundNum)//, float volume)
{


	system->playSound(effectSound[soundNum], 0, false, &effectSoundChannel[soundNum]);


}

void SoundManager::PlayBGM(bgmSound bgmNum)
{
	bool isPlaying;
	bgmSoundChannel[bgmNum]->isPlaying(&isPlaying);
	if (!isPlaying) {

		system->playSound(BgmSound[bgmNum], 0, false, &bgmSoundChannel[bgmNum]);
		//break;
	}

}



// FMOD::System* SoundManager::m_pSystem;
// FMOD::Sound* SoundManager::m_pSound[100];
// FMOD::Channel* SoundManager::m_pChannel[100];
// 
// float SoundManager::m_volume;


//SoundManager::SoundManager()
//{
//
//}
//
//SoundManager::~SoundManager()
//{
//	delete m_pSystem;
//	delete[] m_pSound;
//	delete[] m_pChannel;
//}
//
//SoundManager& SoundManager::GetInstance()
//{
//	static SoundManager* instance = new SoundManager();
//	return *instance;
//}
//
//void SoundManager::SystemInitialize()
//{
//	FMOD::System_Create(&m_pSystem);
//	m_pSystem->init(1000, FMOD_INIT_NORMAL, nullptr);
//}
//
//
//void SoundManager::CreateSound(const char* soundFile, eSound soundChannel, bool isLoop)
//{
//	if (isLoop)
//	{
//		m_pSystem->createSound(soundFile, FMOD_LOOP_NORMAL, 0, &m_pSound[soundChannel]);
//	}
//	else
//	{
//		m_pSystem->createSound(soundFile, FMOD_LOOP_OFF, 0, &m_pSound[soundChannel]);
//	}
//}
//
//void SoundManager::PlaySounds(eSound soundChannel)
//{
//	if (MainBGM <= soundChannel && soundChannel <= SoundCount)
//	{
//		bool isPlaying;
//		m_pChannel[soundChannel]->isPlaying(&isPlaying);
//		if (isPlaying)
//		{
//			m_pChannel[soundChannel]->stop();
//		}
//		m_pSystem->playSound(m_pSound[soundChannel], 0, false, &m_pChannel[soundChannel]);
//	}
//	// 	if (MainBGM <= soundChannel && soundChannel <= CustomerBye)
//	// 	{
//	// 		if (m_pSound[soundChannel] != nullptr)
//	// 
//	// 			m_pSystem->playSound(m_pSound[soundChannel], 0, false, &m_pChannel[soundChannel]);
//	// 		m_pSound[soundChannel] = nullptr;
//	// 
//	// 	}
//
//}
//
//void SoundManager::PlaySounds(eSound soundChannel, const char* path)
//{
//	if (MainBGM <= soundChannel && soundChannel <= SoundCount)
//	{
//		if (m_pSound[soundChannel] != nullptr)
//		{
//			m_pSystem->playSound(m_pSound[soundChannel], 0, false, &m_pChannel[soundChannel]);
//		}
//
//		bool isPlaying = false;
//		m_pChannel[soundChannel]->isPlaying(&isPlaying);
//
//		m_pSound[soundChannel] = nullptr;
//
//// 		if (m_pSound[soundChannel] == nullptr && !isPlaying)
//// 		{
//// 			CreateSound(path, soundChannel, true);
//// 		}
//	}
//}
//
//void SoundManager::PlayEffects(eSound soundChannel, const char* path)
//{
//	if (MainBGM <= soundChannel && soundChannel <= SoundCount)
//	{
//		if (m_pSound[soundChannel] != nullptr)
//		{
//			m_pSystem->playSound(m_pSound[soundChannel], 0, false, &m_pChannel[soundChannel]);
//			m_pSound[soundChannel] = nullptr;
//		} 
//
//		bool isPlaying = false;
//		m_pChannel[soundChannel]->isPlaying(&isPlaying);
//
//
//		if (m_pSound[soundChannel] == nullptr && !isPlaying)
//		{
//			CreateSound(path, soundChannel, false);
//		}
//	}
//}
//
//void SoundManager::StopSound(eSound soundChannel)
//{
//	m_pChannel[soundChannel]->stop();
//}
//
//void SoundManager::SoundVolumeUp(eSound soundChannel, float volume)
//{
//	m_volume += volume;
//	m_pChannel[soundChannel]->setVolume(m_volume);
//}
//
//void SoundManager::SoundVolumeDown(eSound soundChannel, float volume)
//{
//	m_volume -= volume;
//	m_pChannel[soundChannel]->setVolume(m_volume);
//}
//
//void SoundManager::SystemFinalize()
//{
//	m_pSystem->release();
//}
//
//void SoundManager::SoundUpdate()
//{
//	m_pSystem->update();
//}

