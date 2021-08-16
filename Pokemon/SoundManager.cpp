#include "SoundManager.h"
#include <windows.h>
#include <fstream>
#include <tchar.h>
#include "Timer.h"
#include <thread>
#include <chrono>

using std::thread;
using namespace std::chrono;

SoundManager::Sound SoundManager::sound = SoundManager::Sound();

void SoundManager::Sound::SoundFadeIn(void)
{
	while (bgm->GetVolume() < 0.5f)
	{
		bgm->volumeUp();
		Sleep(200);
	}

	isFading = false;
}

void SoundManager::Sound::SoundFadeOut(std::string _bgmName)
{
	while (bgm->GetVolume() > 0.0f)
	{
		bgm->volumeDown();
		Sleep(200);
	}

	delete bgm;

	bgmName = _bgmName;
	bgm = new CSound(GetPath(_bgmName).c_str(), true);
	bgm->play();

	thread t(&SoundManager::Sound::SoundFadeIn, this);
	t.detach();
}

std::string SoundManager::Sound::GetPath(std::string name)
{
	std::string ret = path + name + ".mp3";
	return ret;
}

void SoundManager::Sound::init()
{
	loadEffects();
}

void SoundManager::Sound::reset()
{
	for (auto& e : effects)
		delete e.second;
}

void SoundManager::Sound::_fadeIn()
{
	double timer = 0.0f;

	auto prevClock = high_resolution_clock::now();

	while (bgm->GetVolume() < 0.5f)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		timer += deltaTime;

		if (timer > 0.16f)
		{
			timer = 0.0f;
			bgm->volumeUp();
		}

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	isFading = false;
}

void SoundManager::Sound::_fadeOut(std::string name)
{
	double timer = 0.0f;

	auto prevClock = high_resolution_clock::now();

	while (bgm->GetVolume() > 0.0f)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		timer += deltaTime;

		if (timer > 0.16f)
		{
			timer = 0.0f;
			bgm->volumeDown();
		}

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	delete bgm;

	bgmName = name;
	bgm = new CSound(GetPath(name).c_str(), true);
	bgm->play();

	thread t(&SoundManager::Sound::_fadeIn, this);
	t.detach();
}

void SoundManager::Sound::chageBgmWithFade(std::string name)
{
	if (bgmName != name)
	{
		if (!isFading)
		{
			if (bgm == NULL)
			{
				bgmName = name;
				bgm = new CSound(GetPath(name).c_str(), true);
				bgm->play();
			}
			else
			{
				isFading = true;
				thread t(&SoundManager::Sound::_fadeOut, this, name);
				t.detach();
			}
		}
	}
}

void SoundManager::Sound::chageBgmWithoutFade(std::string name, bool loop)
{
	if (!isFading)
	{
		if (bgm != NULL)
			delete bgm;

		bgmName = name;
		bgm = new CSound(GetPath(name).c_str(), loop);
		bgm->play();
	}
}

void SoundManager::Sound::loadEffects()
{
	WIN32_FIND_DATA findData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR fullPath[] = _T("data/sound/effect/*.*");

	hFind = FindFirstFile(fullPath, &findData);

	if (hFind == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Invalid handle value! Please check your path...");

	TCHAR TfilePath[256];
	char filePath[256];
	char fileName[256];

	while (FindNextFile(hFind, &findData))
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			_stprintf_s(TfilePath, _T("data/sound/effect/%s"), findData.cFileName);

			WideCharToMultiByte(CP_ACP, 0, TfilePath, 256, filePath, 256, NULL, NULL);
			WideCharToMultiByte(CP_ACP, 0, findData.cFileName, 256, fileName, 256, NULL, NULL);

			fileName[strlen(fileName) - 4] = 0;
			std::string nameStr(fileName);

			CSound* newSound = new CSound(filePath, false);
			newSound->mute();

			effects[nameStr] = newSound;
		}
	}
}

void SoundManager::ChangeBgmWithFade(std::string name)
{
	sound.chageBgmWithFade(name);
}

void SoundManager::ChangeBgmWithoutFade(std::string name, bool loop)
{
	sound.chageBgmWithoutFade(name, loop);
}

void SoundManager::PlayEffect(std::string name)
{
	sound.effects[name]->play();
}

void SoundManager::PlayBgm()
{
	if (sound.bgm != NULL)
		sound.bgm->play();
}

void SoundManager::StopBgm()
{
	if (sound.bgm != NULL)
		sound.bgm->stop();
}
