#pragma once

#include "fmod.hpp"
#include "eSound.h"
#include "bgmSound.h"


class SoundManager
{
private:
	SoundManager();

	~SoundManager();

	FMOD::System* system;
	FMOD::Sound* effectSound[SoundCount];
	FMOD::Sound* BgmSound[bgmCount];
	FMOD::Channel* effectSoundChannel[SoundCount];
	FMOD::Channel* bgmSoundChannel[bgmCount];

public:
	bool playCheck;
	static SoundManager& GetInstance();
	void SystemInitialize();
	void CreateSound(const char* soundFile, eSound soundNum, bool isLoop);
	void CreateBGM(const char* soundFile, bgmSound bgmNum, bool isLoop);
	void StopSound(eSound soundNum);
	void StopBGM(bgmSound bgmNum);
	void PlaySounds(eSound soundNum);//, float volume);
	void PlayBGM(bgmSound bgmNum);//, float volume);
	void Finalize();
	void SoundUpdate();

};


