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

Audio* SoundSystem::PlayLoop(const std::string& filePath, const float& volume)
{
	Audio* newSound = m_SoundEngine->play2D(m_SoundSourceList[filePath], true, false, true);
	newSound->setVolume(volume);
	m_SoundList[filePath] = newSound;
	return newSound;
}

void SoundSystem::PlayOnce(const std::string& filePath, const float& volume)
{
	m_SoundSourceList[filePath]->setDefaultVolume(volume);
	m_SoundEngine->play2D(m_SoundSourceList[filePath], false);
}

Audio* SoundSystem::GetSound(const std::string& filePath)
{
	return m_SoundList[filePath];
}

void SoundSystem::FreeSound()
{
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