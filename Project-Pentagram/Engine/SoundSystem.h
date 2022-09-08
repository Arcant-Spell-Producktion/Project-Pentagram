#pragma once

#include <irrklang/irrKlang.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "Engine/AudioGroup.h"

class SoundSystem
{
	private:
		irrklang::ISoundEngine* m_SoundEngine;
		std::map<std::string, AudioSource*> m_SoundSourceList;
		std::map<std::string, Audio*> m_SoundList;
		std::map<std::string, AudioGroup*> m_AudioGroupList;
		bool m_IsPaused = false;

		void InitSoundEngine();
	public:
		SoundSystem();

		// SoundEngine Function
		void SetMasterVolume(const float& volume);
		void SetPauseAll(const bool& willPaused);
		bool isAllPaused();

		// Audio Grouping
		AudioGroup* PlayGroupAudio(const std::string& groupName, const std::vector<std::string>& filePathList, const float& volume = 1.0f, const float& playbackSpeed = 1.0f);
		AudioGroup* FindAudioGroup(const std::string& groupName);

		// Audio Playing
		Audio* PlayLoop(const std::string& filePath, const float& volume = 1.0f, const float& playbackSpeed = 1.0f);
		void PlayOnce(const std::string& filePath, const float& volume = 1.0f);
		void SetPause(const std::string& filePath, const bool& willPaused);
		bool IsPause(const std::string& filePath);
		Audio* GetSound(const std::string& filePath);

		// Free Memory
		void FreeSound();
		void FreeEngine();
};