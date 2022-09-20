#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
	InitSoundEngine();
	// Load All BGM
	LoadFile("Audio/BGM", m_BGMSourceList);
	// Load All SFX
	LoadFile("Audio/SFX", m_SFXSourceList);
}

// ----------------- Audio Grouping ----------------- 
AudioGroup* SoundSystem::PlayGroupAudio(const std::string& groupName, const std::vector<std::string>& filePathList, const float& volume, const float& playbackSpeed)
{
	AudioGroup* audioGroup = new AudioGroup(groupName);
	for (const std::string fileName : filePathList)
	{
		Audio* newSound = m_SoundEngine->play2D(m_BGMSourceList[fileName], true, false, true);
		
		// Handle Error in case fileName are not exist in Folder
		ArcantAssert(newSound != nullptr, fileName + " Doesn't exist in Audio Folder\n");
		
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
	if (m_AudioGroupList.find(groupName) == m_AudioGroupList.end())
	{
		return nullptr;
	}

	return m_AudioGroupList[groupName];
}

// ----------------- Audio Playing ----------------- 
Audio* SoundSystem::PlayBGM(const std::string& fileName, const bool& isLoop, const float& playbackSpeed)
{
	// Handle Error : fileName doesn't exist
	ArcantAssert(m_BGMSourceList.find(fileName) == m_BGMSourceList.end(), fileName + " Doesn't exist in Audio Folder\n");

	m_BGMSourceList[fileName]->setDefaultVolume(m_BGMVolume * m_MasterVolume);
	Audio* newSound = m_SoundEngine->play2D(m_BGMSourceList[fileName], isLoop, false, true);
	newSound->setVolume(m_BGMVolume * m_MasterVolume);
	newSound->setPlaybackSpeed(playbackSpeed);
	m_BGMSoundList[fileName] = newSound;
	return newSound;
}
Audio* SoundSystem::PlaySFX(const std::string& fileName, const bool& isLoop, const float& playbackSpeed)
{
	// Handle Error : fileName doesn't exist
	ArcantAssert(m_SFXSourceList.find(fileName) == m_SFXSourceList.end(), fileName + " Doesn't exist in Audio Folder\n");

	m_SFXSourceList[fileName]->setDefaultVolume(m_SFXVolume* m_MasterVolume);
	Audio* newSound = m_SoundEngine->play2D(m_SFXSourceList[fileName], isLoop, false, true);
	newSound->setVolume(m_SFXVolume * m_MasterVolume);
	newSound->setPlaybackSpeed(playbackSpeed);
	m_SFXSoundList[fileName] = newSound;
	return newSound;
}

// ----------------- Audio Components -----------------
void SoundSystem::SetPause(const std::string& fileName, const bool& willPaused)
{
	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		m_BGMSoundList[fileName]->setIsPaused(willPaused);
		return;
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		m_SFXSoundList[fileName]->setIsPaused(willPaused);
		return;
	}
	
	// Handle Error : fileName doesn't exist in List
	// Fixed by checking that you already play this fileName before
	ArcantAssert(nullptr, fileName + " Doesn't exist in SoundList\n");
}
void SoundSystem::SetPause(const std::string& groupName, const std::string& fileName, const bool& willPaused)
{
	// Handle Error : groupName doesn't exist in List
	// Fixed by checking that you already play this groupName before
	ArcantAssert(m_AudioGroupList.find(groupName) != m_AudioGroupList.end(), groupName + " Doesn't exist in AudioGroup List\n");

	m_AudioGroupList[groupName]->GetAudio(fileName)->setIsPaused(willPaused);
}
bool SoundSystem::IsPause(const std::string& fileName)
{
	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		return m_BGMSoundList[fileName]->getIsPaused();
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		return m_SFXSoundList[fileName]->getIsPaused();
	}

	// Handle Error : fileName doesn't exist in List
	// Fixed by checking that you already play this fileName before
	ArcantAssert(nullptr, fileName + " Doesn't exist in SoundList\n");
}
bool SoundSystem::IsPause(const std::string& groupName, const std::string& fileName)
{
	// Handle Error : groupName doesn't exist in List
	// Fixed by checking that you already play this groupName before
	ArcantAssert(m_AudioGroupList.find(groupName) != m_AudioGroupList.end(), groupName + " Doesn't exist in AudioGroup List\n");

	return m_AudioGroupList[groupName]->GetAudio(fileName)->getIsPaused();
}
Audio* SoundSystem::GetSound(const std::string& fileName)
{
	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		return m_BGMSoundList[fileName];
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		return m_SFXSoundList[fileName];
	}
	return nullptr;
}
Audio* SoundSystem::GetSound(const std::string& groupName, const std::string& fileName)
{
	// Handle Error : groupName doesn't exist in List
	// Fixed by checking that you already play this groupName before
	ArcantAssert(m_AudioGroupList.find(groupName) != m_AudioGroupList.end(), groupName + " Doesn't exist in AudioGroup List\n");

	return m_AudioGroupList[groupName]->GetAudio(fileName);
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

	// Handle Error : fileName doesn't exist in List
	// Fixed by checking that you already play this fileName before
	ArcantAssert(nullptr, fileName + " Doesn't exist in SoundList\n");
}
bool SoundSystem::IsMute(const std::string& groupName, const std::string& fileName) 
{ 
	// Handle Error : groupName doesn't exist in List
	// Fixed by checking that you already play this groupName before
	ArcantAssert(m_AudioGroupList.find(groupName) != m_AudioGroupList.end(), groupName + " Doesn't exist in AudioGroup List\n");

	return m_AudioGroupList[groupName]->GetAudio(fileName)->getVolume() < 0.0f; 
}
void SoundSystem::Mute(const std::string& fileName)
{
	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		m_BGMSoundList[fileName]->setVolume(MUTE);
		return;
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		m_SFXSoundList[fileName]->setVolume(MUTE);
		return;
	}

	// Handle Error : fileName doesn't exist in List
	// Fixed by checking that you already play this fileName before
	ArcantAssert(nullptr, fileName + " Doesn't exist in SoundList\n");
}
void SoundSystem::Mute(const std::string& groupName, const std::string& fileName)
{
	// Handle Error : groupName doesn't exist in List
	// Fixed by checking that you already play this groupName before
	ArcantAssert(m_AudioGroupList.find(groupName) != m_AudioGroupList.end(), groupName + " Doesn't exist in AudioGroup List\n");

	Audio* curAudio = m_AudioGroupList[groupName]->GetAudio(fileName);
	curAudio->setVolume(MUTE);
}
void SoundSystem::UnMute(const std::string& fileName)
{

	if (m_BGMSoundList.find(fileName) != m_BGMSoundList.end())
	{
		m_BGMSoundList[fileName]->setVolume(m_BGMVolume * m_MasterVolume);
		return;
	}
	else if (m_SFXSoundList.find(fileName) != m_SFXSoundList.end())
	{
		m_SFXSoundList[fileName]->setVolume(m_SFXVolume * m_MasterVolume);
		return;
	}

	// Handle Error : fileName doesn't exist in List
	// Fixed by checking that you already play this fileName before
	ArcantAssert(nullptr, fileName + " Doesn't exist in SoundList\n");
}
void SoundSystem::UnMute(const std::string& groupName, const std::string& fileName)
{
	// Handle Error : groupName doesn't exist in List
	// Fixed by checking that you already play this groupName before
	ArcantAssert(m_AudioGroupList.find(groupName) != m_AudioGroupList.end(), groupName + " Doesn't exist in AudioGroup List\n");

	Audio* curAudio = m_AudioGroupList[groupName]->GetAudio(fileName);
	curAudio->setVolume(m_BGMVolume * m_MasterVolume);
}

// ----------------- Getter ----------------- 
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
void SoundSystem::SetPauseAll(const bool& willPaused)
{
	m_SoundEngine->setAllSoundsPaused(willPaused);
	m_IsPaused = willPaused;
}

// ----------------- Setter ----------------- 
float SoundSystem::GetMasterVolume() const 
{ 
	return m_MasterVolume; 
}
float SoundSystem::GetSFXVolume() const 
{ 
	return m_SFXVolume; 
}
float SoundSystem::GetBGMVolume() const 
{ 
	return m_BGMVolume; 
}
bool SoundSystem::isAllPaused() const
{
	return m_IsPaused;
}

// ----------------- Free Memory ----------------- 
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


// ----------------- Private Function----------------- 
void SoundSystem::InitSoundEngine()
{
	m_SoundEngine = irrklang::createIrrKlangDevice();

	if (!m_SoundEngine)
	{
		std::cerr << "Error : Failed to Initialize Sound Engine\n";
		exit(EXIT_FAILURE);
	}
}

void SoundSystem::LoadFile(const std::string& filePath, std::map<std::string, AudioSource*>& listContainer)
{
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator(filePath))
	{
		std::string filePathString = (dirEntry.path()).string();
		if (dirEntry.is_directory())
		{
			LoadFile(filePathString, listContainer);
		}
		else
		{
			std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
			listContainer[filePathString] = m_SoundEngine->addSoundSourceFromFile(filePathString.c_str(), irrklang::ESM_AUTO_DETECT, true);
		}
	}
}