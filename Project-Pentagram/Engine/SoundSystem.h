#pragma once

#include <irrklang/irrKlang.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "Engine/AudioGroup.h"
#include "Utilities/ArcantAssert.h"

#define MUTE -1.0f

class SoundSystem
{
	private:
		// Loaded before GameStart
		irrklang::ISoundEngine* m_SoundEngine;
		std::map<std::string, AudioSource*> m_BGMSourceList;
		std::map<std::string, AudioSource*> m_SFXSourceList;

		// Contain in run-time
		std::map<std::string, Audio*> m_BGMSoundList;
		std::map<std::string, Audio*> m_SFXSoundList;
		std::map<std::string, AudioGroup*> m_AudioGroupList;
		bool m_IsPaused = false;
		float m_MasterVolume = 1.0f;
		float m_BGMVolume = 1.0f;
		float m_SFXVolume = 1.0f;

		void InitSoundEngine();

	public:
		SoundSystem();

		void SetPauseAll(const bool& willPaused);
		bool isAllPaused();

		// Audio Grouping
		AudioGroup* PlayGroupAudio(const std::string& groupName, const std::vector<std::string>& filePathList, const float& volume = 1.0f, const float& playbackSpeed = 1.0f);
		AudioGroup* FindAudioGroup(const std::string& groupName);

		// Audio Playing
		Audio* PlayBGM(const std::string& fileName, const bool& isLoop, const float& playbackSpeed = 1.0f);
		Audio* PlaySFX(const std::string& fileName, const bool& isLoop, const float& playbackSpeed = 1.0f);
		void SetPause(const std::string& fileName, const bool& willPaused);
		void SetPause(const std::string& groupName, const std::string& fileName, const bool& willPaused);
		bool IsPause(const std::string& fileName);
		bool IsPause(const std::string& groupName, const std::string& fileName);
		Audio* GetSound(const std::string& fileName);
		Audio* GetSound(const std::string& groupName, const std::string& fileName);
		bool IsMute(const std::string& fileName);
		bool IsMute(const std::string& groupName, const std::string& fileName);
		void Mute(const std::string& fileName);
		void Mute(const std::string& groupName, const std::string& fileName);
		void UnMute(const std::string& fileName);
		void UnMute(const std::string& groupName, const std::string& fileName);


		// Getter - Setter
		void SetMasterVolume(const float& volume);
		void SetSFXVolume(const float& volume);
		void SetBGMVolume(const float& volume);

		float GetMasterVolume();
		float GetSFXVolume();
		float GetBGMVolume();

		// Free Memory
		void FreeSound();
		void FreeEngine();
};