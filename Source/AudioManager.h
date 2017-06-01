#pragma once

#include <Engine/OGLGame.h>

namespace irrklang
{
	class ISoundEngine;
}

// Plays audio that can be passed in
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	 void playAudio(const char*& sound);
	 void tick();

protected:

private:
	bool initAudio();
	std::unique_ptr<irrklang::ISoundEngine> audio_engine = nullptr;
};