#include <irrKlang.h>

#include "Actions.h"
#include "AudioManager.h"



AudioManager::AudioManager()
{
	initAudio();
}



AudioManager::~AudioManager()
{
	audio_engine->stopAllSounds();
}



// receives the name of audio to play and plays it
void AudioManager::playAudio(const char*& sound)
{
	audio_engine->play2D(sound, false);
}



bool AudioManager::initAudio()
{
	using namespace irrklang;
	audio_engine.reset(createIrrKlangDevice());

	if (!audio_engine)
	{
		return false; // error starting up the engine
	}

	return true;
}



void AudioManager::tick()
{
	// If player is not in game stop all sound
	if (game_state == GameState::MENU || game_state == GameState::PAUSE)
	{
		audio_engine->stopAllSounds();
	}
}