#pragma once

#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "CSound.h"
#include <string>
#include <stddef.h>
#include <unordered_map>

using std::unordered_map;

class SoundManager
{
private:

	class Sound
	{
		friend SoundManager;
		
	private:

		const std::string path = "data/sound/bgm/";

	private:

		bool isFading;
		std::string bgmName;
		CSound* bgm;

		unordered_map<std::string, CSound*> effects;

	private:

		void _fadeIn();
		void _fadeOut(std::string name);
		std::string GetPath(std::string name);

	private:
			
		Sound() : bgm(NULL), isFading(false) { }
		~Sound() = default;

	private:

		void init();
		void reset();

		void chageBgmWithFade(std::string name);
		void chageBgmWithoutFade(std::string name, bool loop);
		void loadEffects();
	};

private:

	static Sound sound;

	SoundManager() = delete;
	~SoundManager() = delete;

public:

	static void Init() { sound.init(); }
	static void Reset() { sound.reset(); }

	static void ChangeBgmWithFade(std::string name);
	static void ChangeBgmWithoutFade(std::string name, bool loop); 

	static void PlayEffect(std::string name);
	static void PlayBgm();
	static void StopBgm();

};

#define SM SoundManager

#endif // !__SOUNDMANAGER_H__
