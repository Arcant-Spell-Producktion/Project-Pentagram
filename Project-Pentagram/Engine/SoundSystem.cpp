#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
	InitSoundEngine();
	// Load All BGM
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator("Audio/BGM"))
	{
		std::string filePathString = (dirEntry.path()).string();
		std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
		m_BGMSourceList[filePathString] = m_SoundEngine->addSoundSourceFromFile(filePathString.c_str(), irrklang::ESM_AUTO_DETECT, true);
	}
	// Load All SFX
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator("Audio/SFX"))
	{
		std::string filePathString = (dirEntry.path()).string();
		std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
		m_SFXSourceList[filePathString] = m_SoundEngine->addSoundSourceFromFile(filePathString.c_str(), irrklang::ESM_AUTO_DETECT, true);
	}
}

void SoundSystem::SetPauseAll(const bool& willPaused)
{
	m_SoundEngine->setAllSoundsPaused(willPaused);
	m_IsPaused = willPaused;
}
bool SoundSystem::isAllPaused()
{
	return m_IsPaused;
}

// Audio Grouping Implement
AudioGroup* SoundSystem::PlayGroupAudio(const std::string& groupName, const std::vector<std::string>& filePathList, const float& volume, const float& playbackSpeed)
{
	AudioGroup* audioGroup = new AudioGroup(groupName);
	for (const std::string fileName : filePathList)
	{
		Audio* newSound = m_SoundEngine->play2D(m_BGMSourceList[fileName], true, false, true);
		newSound->setVolume(volume);
		newSound->setPlaybackSpeed(playbackSpeed);
		m_BGMSoundList[fileName] = newSound;
		audioGroup->AddAudio(fileName, newSound);
	}
	m_AudioGroupList[groupName] = audioGroup;
	return audioGroup;
}
AudioGroup* SoundSystem::FindAudioGroup(const std::string& groupName)
{
	return m_AudioGroupList[groupName];
}

// Audio Implement
Audio* SoundSystem::PlayBGM(const std::string& filePath, const bool& isLoop, const float& playbackSpeed)
{
	m_BGMSourceList[filePath]->setDefaultVolume(m_BGMVolume * m_MasterVolume);
	Audio* newSound = m_SoundEngine->play2D(m_BGMSourceList[filePath], isLoop, false, true);
	newSound->setVolume(m_BGMVolume * m_MasterVolume);
	newSound->setPlaybackSpeed(playbackSpeed);
	m_BGMSoundList[filePath] = newSound;
	return newSound;
}
Audio* SoundSystem::PlaySFX(const std::string& filePath, const bool& isLoop, const float& playbackSpeed)
{
	m_SFXSourceList[filePath]->setDefaultVolume(m_SFXVolume* m_MasterVolume);
	Audio* newSound = m_SoundEngine->play2D(m_SFXSourceList[filePath], isLoop, false, true);
	newSound->setVolume(m_SFXVolume * m_MasterVolume);
	newSound->setPlaybackSpeed(playbackSpeed);
	m_SFXSoundList[filePath] = newSound;
	return newSound;
}

void SoundSystem::SetPause(const std::string& filePath, const bool& willPaused)
{
	if (m_BGMSoundList.find(filePath) != m_BGMSoundList.end())
	{
		m_BGMSoundList[filePath]->setIsPaused(willPaused);
	}
	else if (m_SFXSoundList.find(filePath) != m_SFXSoundList.end())
	{
		m_SFXSoundList[filePath]->setIsPaused(willPaused);
	}
}
bool SoundSystem::IsPause(const std::string& filePath)
{
	if (m_BGMSoundList.find(filePath) != m_BGMSoundList.end())
	{
		return m_BGMSoundList[filePath]->getIsPaused();
	}
	else if (m_SFXSoundList.find(filePath) != m_SFXSoundList.end())
	{
		return m_SFXSoundList[filePath]->getIsPaused();
	}
	return false;
}
Audio* SoundSystem::GetSound(const std::string& filePath)
{
	if (m_BGMSoundList.find(filePath) != m_BGMSoundList.end())
	{
		return m_BGMSoundList[filePath];
	}
	else if (m_SFXSoundList.find(filePath) != m_SFXSoundList.end())
	{
		return m_SFXSoundList[filePath];
	}
	return nullptr;
}


bool SoundSystem::IsMute(const std::string& fileName) 
{
	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		return m_BGMSoundList[fileName]->getVolume() < 0.0f;
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		return m_SFXSoundList[fileName]->getVolume() < 0.0f;
	}
}
void SoundSystem::Mute(const std::string& fileName)
{
	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		m_BGMSoundList[fileName]->setVolume(MUTE);
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		m_SFXSoundList[fileName]->setVolume(MUTE);
	}
}
void SoundSystem::UnMute(const std::string& fileName)
{

	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		m_BGMSoundList[fileName]->setVolume(m_BGMVolume * m_MasterVolume);
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		m_SFXSoundList[fileName]->setVolume(m_SFXVolume * m_MasterVolume);
	}
}

bool SoundSystem::IsMute(const std::string& groupName, const std::string& fileName) { return m_AudioGroupList[groupName]->GetAudio(fileName)->getVolume() < 0.0f; }
void SoundSystem::Mute(const std::string& groupName, const std::string& fileName)
{
	Audio* curAudio = m_AudioGroupList[groupName]->GetAudio(fileName);
	curAudio->setVolume(MUTE);
}
void SoundSystem::UnMute(const std::string& groupName, const std::string& fileName)
{
	Audio* curAudio = m_AudioGroupList[groupName]->GetAudio(fileName);
	curAudio->setVolume(m_BGMVolume * m_MasterVolume);
}

// Getter - Setter Implement
void SoundSystem::SetMasterVolume(const float& volume)
{
	this->m_MasterVolume = volume;
	this->m_SoundEngine->setSoundVolume(m_MasterVolume);
}
void SoundSystem::SetSFXVolume(const float& volume)
{
	this->m_SFXVolume = volume;
	for (auto it = m_SFXSourceList.begin(); it != m_SFXSourceList.end(); it++)
	{
		it->second->setDefaultVolume(m_MasterVolume * m_SFXVolume);
	}
	for (auto it = m_SFXSoundList.begin(); it != m_SFXSoundList.end(); it++)
	{
		if (it->second->getVolume() < 0.0f)
		{
			continue;
		}
		it->second->setVolume(m_MasterVolume * m_SFXVolume);
	}
}
void SoundSystem::SetBGMVolume(const float& volume)
{
	this->m_BGMVolume = volume;
	for (auto it = m_BGMSourceList.begin(); it != m_BGMSourceList.end(); it++)
	{
		it->second->setDefaultVolume(m_MasterVolume * m_BGMVolume);
	}
	for (auto it = m_BGMSoundList.begin(); it != m_BGMSoundList.end(); it++)
	{
		if (it->second->getVolume() < 0.0f)
		{
			continue;
		}
		it->second->setVolume(m_MasterVolume * m_BGMVolume);
	}
}

float SoundSystem::GetMasterVolume() { return m_MasterVolume; }
float SoundSystem::GetSFXVolume() { return m_SFXVolume; }
float SoundSystem::GetBGMVolume() { return m_BGMVolume; }

// Free Memory
void SoundSystem::FreeSound()
{
	m_IsPaused = false;
	// Stop All Sound
	m_SoundEngine->stopAllSounds();

	// Clear All Sound List
	for (auto it = m_BGMSoundList.begin(); it != m_BGMSoundList.end(); it++)
	{
		it->second->drop();
	}
	m_BGMSoundList.clear();
	for (auto it = m_SFXSoundList.begin(); it != m_SFXSoundList.end(); it++)
	{
		it->second->drop();
	}
	m_SFXSoundList.clear();

	// Clear Audio Group
	for (auto it = m_AudioGroupList.begin(); it != m_AudioGroupList.end(); it++)
	{
		delete it->second;
	}
	m_AudioGroupList.clear();
}

void SoundSystem::FreeEngine()
{
	m_SoundEngine->drop();
}

void SoundSystem::InitSoundEngine()
{
	m_SoundEngine = irrklang::createIrrKlangDevice();

	if (!m_SoundEngine)
	{
		std::cerr << "Error : Failed to Initialize Sound Engine\n";
		exit(EXIT_FAILURE);
	}
}