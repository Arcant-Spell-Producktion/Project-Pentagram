#pragma once

#include <irrklang/irrKlang.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "Utilities/Singleton.h"
#include "Utilities/ArcantAssert.h"

using Audio = irrklang::ISound;
using AudioSource = irrklang::ISoundSource;

class AudioEngine : public Singleton<AudioEngine>
{
	private:
		// Loaded before GameStart
		irrklang::ISoundEngine* m_AudioEngine;
		std::map<std::string, AudioSource*> m_BGMSourceList;
		std::map<std::string, AudioSource*> m_SFXSourceList;

		float m_MasterVolume = 1.0f;
		float m_BGMVolume = 1.0f;
		float m_SFXVolume = 1.0f;

		void InitSoundEngine();
		void LoadFile(const std::string& filePath, std::map<std::string, AudioSource*>& listContainer);
			
	public:
		AudioEngine();
		void LoadResource();

		AudioSource* findSFXAudioSource(const std::string& filePath);
		AudioSource* findBGMAudioSource(const std::string& filePath);

		irrklang::ISoundEngine* GetEngine();
		float GetMasterVolume();

		// ----------------- Free Memory ----------------- 
		void Free();
};