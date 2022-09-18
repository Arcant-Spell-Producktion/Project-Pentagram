#pragma once

#include <irrklang/irrKlang.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Utilities/ArcantAssert.h"

using Audio = irrklang::ISound;
using AudioSource = irrklang::ISoundSource;

class AudioGroup
{
	private:
		std::string m_Name;
		std::map<std::string, Audio*> m_SubSoundList;
	
	public:
		AudioGroup(const std::string& groupName);
		void AddAudio(const std::string& filePath, Audio* audio);
		void RemoveAudio(const std::string& filePath);
		void SetVolume(const float& volume);
		void SetVolume(const std::string& filePath, const float& volume);

		Audio* GetAudio(const std::string& audio);
		std::string GetGroupName() const;

};