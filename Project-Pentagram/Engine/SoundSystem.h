#pragma once

#include <irrklang/irrKlang.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

using Audio = irrklang::ISound;
using AudioSource = irrklang::ISoundSource;

class SoundSystem
{
	private:
		irrklang::ISoundEngine* m_SoundEngine;
		std::map<std::string, AudioSource*> m_SoundSourceList;
		std::map<std::string, Audio*> m_SoundList;

		void InitSoundEngine();
	public:
		SoundSystem();
		Audio* PlayLoop(const std::string& filePath, const float& volume);
		void PlayOnce(const std::string& filePath, const float& volume);
		Audio* GetSound(const std::string& filePath);
		void FreeSound();
		void FreeEngine();
};