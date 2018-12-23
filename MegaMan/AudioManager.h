//#pragma once
#ifndef _DXAUDIO_H
#define _DXAUDIO_H

#include "dsutil.h"
#include "Sound.h"

enum LIST_AUDIO
{
	AUDIO_STARTGAME,
	AUDIO_FIRSTSTAGE,
	AUDIO_SHOT_BULLET,
	AUDIO_ROCK_JUMP,
	AUDIO_ROCK_SURFING,
	AUDIO_ROCK_DIE,
	AUDIO_ROCK_PICKUP,
	AUDIO_BOSS_DIE,
	AUDIO_BOSSSTAGE,
	AUDIO_CHARGE,
	AUDIO_CREP_DIE,
	AUDIO_COUNT
};

class AudioManager
{
	static AudioManager* instance;
	int Init_DirectSound(HWND);
	AudioManager();

	GSoundManager *dsound;
	GSound** sounds;
public:
	static AudioManager* getInstance();
	GSound *LoadSound(char *);
	void Play(LIST_AUDIO);
	void LoopSound(LIST_AUDIO);
	void StopSound(LIST_AUDIO);
	
	~AudioManager();
};
#endif

