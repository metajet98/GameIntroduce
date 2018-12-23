#include "AudioManager.h"
#include "WindowGame.h"


AudioManager * AudioManager::instance = 0;
AudioManager * AudioManager::getInstance()
{
	if (instance == 0) instance = new AudioManager();
	return instance;
}

GSound * AudioManager::LoadSound(char *filename)
{
	HRESULT result;

	//create local reference to wave data
	GSound *wave;

	//attempt to load the wave file
	result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		MessageBox(WINDOW->getHandleWindow(), "[FAILED] Can not set the primary buffer", "Loi", MB_ICONERROR);
		return NULL;
	}
	//GLTrace("Sound file has been loaded");
	//MessageBox(hwnd, "[FAILED] Can not set the primary buffer", "Loi", MB_ICONERROR);
	//return the wave
	return wave;
}

void AudioManager::Play(LIST_AUDIO item)
{
	sounds[item]->Play();
}

void AudioManager::LoopSound(LIST_AUDIO item)
{
	sounds[item]->Play(0, DSBPLAY_LOOPING);
}

void AudioManager::StopSound(LIST_AUDIO item)
{
	sounds[item]->Stop();
}


int AudioManager::Init_DirectSound(HWND hwnd)
{
	HRESULT result;

	//create DirectSound manager object
	dsound = new GSoundManager();

	//initialize DirectSound
	result = dsound->Initialize(hwnd, DSSCL_PRIORITY);
	if (result != DS_OK)
	{

		MessageBox(hwnd, "[FAILED] Can not init directx sound", "Loi", MB_ICONERROR);
		return 0;
		//return 1;
	}

	//set the primary buffer format
	result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK)
	{

		MessageBox(hwnd, "[FAILED] Can not set the primary buffer", "Loi", MB_ICONERROR);
		return 0;
		//return 1;
	}
	//return success
	//GLTrace("Directx Sound has been success init");
	//MessageBox(hwnd, "Directx Sound has been success init", "Loi", MB_ICONERROR);
	return 1;
}

AudioManager::AudioManager()
{
	Init_DirectSound(WINDOW->getHandleWindow());
	sounds = new GSound*[AUDIO_COUNT];

	sounds[AUDIO_STARTGAME] = LoadSound((char*)"Data\\Audio\\Sound\\Title_Theme.wav");
	sounds[AUDIO_FIRSTSTAGE] = LoadSound((char*)"Data\\Audio\\Sound\\First_Stage.wav");
	sounds[AUDIO_SHOT_BULLET] = LoadSound((char*)"Data\\Audio\\Sound\\Mega_man_shoot_single_bullet_2.wav");
	sounds[AUDIO_ROCK_JUMP] = LoadSound((char*)"Data\\Audio\\Sound\\Jump_1.wav");
	sounds[AUDIO_ROCK_SURFING] = LoadSound((char*)"Data\\Audio\\Sound\\surfing_2.wav");
	sounds[AUDIO_ROCK_DIE] = LoadSound((char*)"Data\\Audio\\Sound\\MegaDie.wav");
	sounds[AUDIO_ROCK_PICKUP] = LoadSound((char*)"Data\\Audio\\Sound\\Pick_up_item.wav");
	sounds[AUDIO_BOSS_DIE] = LoadSound((char*)"Data\\Audio\\Sound\\Boss_die_2.wav");
	sounds[AUDIO_BOSSSTAGE] = LoadSound((char*)"Data\\Audio\\Sound\\Blast_Hornet.wav");
	sounds[AUDIO_CHARGE] = LoadSound((char*)"Data\\Audio\\Sound\\Charge_2.wav");
	sounds[AUDIO_CREP_DIE] = LoadSound((char*)"Data\\Audio\\Sound\\Creep_die.wav");
}


AudioManager::~AudioManager()
{
	if (sounds != NULL) {
		for (int i = 0; i < AUDIO_COUNT; i++) {
			delete sounds[i];
		}
		delete[]sounds;
	}
}
