#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
	InitSoundEngine();
	// Load All Audio
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator("Audio"))
	{
		std::string filePathString = (dirEntry.path()).string();
		std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
		m_SoundSourceList[filePathString] = m_SoundEngine->addSoundSourceFromFile(filePathString.c_str(), irrklang::ESM_AUTO_DETECT, true);
	}
}

// Sound Engine Implement
void SoundSystem::SetMasterVolume(const float& volume)
{
	m_SoundEngine->setSoundVolume(volume);
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

// Audio Implement
Audio* SoundSystem::PlayLoop(const std::string& filePath, const float& volume, const float& playbackSpeed)
{
	Audio* newSound = m_SoundEngine->play2D(m_SoundSourceList[filePath], true, false, true);
	newSound->setVolume(volume);
	newSound->setPlaybackSpeed(playbackSpeed);
	m_SoundList[filePath] = newSound;
	return newSound;
}
void SoundSystem::PlayOnce(const std::string& filePath, const float& volume)
{
	m_SoundSourceList[filePath]->setDefaultVolume(volume);
	m_SoundEngine->play2D(m_SoundSourceList[filePath], false);
}
void SoundSystem::SetPause(const std::string& filePath, const bool& willPaused)
{
	m_SoundList[filePath]->setIsPaused(willPaused);
}
bool SoundSystem::IsPause(const std::string& filePath)
{
	return m_SoundList[filePath]->getIsPaused();
}
Audio* SoundSystem::GetSound(const std::string& filePath)
{
	return m_SoundList[filePath];
}

// Free Memory
void SoundSystem::FreeSound()
{
	m_IsPaused = false;
	m_SoundEngine->stopAllSounds();
	for (auto it = m_SoundList.begin(); it != m_SoundList.end(); it++)
	{
		it->second->drop();
	}
	m_SoundList.clear();
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