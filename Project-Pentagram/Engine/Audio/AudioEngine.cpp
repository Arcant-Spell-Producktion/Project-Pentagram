#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
	InitSoundEngine();
}
void AudioEngine::LoadResource()
{
	// Load All BGM
	LoadFile("Audio/BGM", m_BGMSourceList);
	// Load All SFX
	LoadFile("Audio/SFX", m_SFXSourceList);
}

AudioSource* AudioEngine::findSFXAudioSource(const std::string& filePath)
{
	if (m_SFXSourceList.find(filePath) == m_SFXSourceList.end())
	{
		return nullptr;
	}
	return m_SFXSourceList[filePath];
}
AudioSource* AudioEngine::findBGMAudioSource(const std::string& filePath)
{
	if (m_BGMSourceList.find(filePath) == m_BGMSourceList.end())
	{
		return nullptr;
	}
	return m_BGMSourceList[filePath];
}

void AudioEngine::SetMasterVolume(const float& volume)
{
	m_MasterVolume = volume;
}
void AudioEngine::SetBGMVolume(const float& volume)
{
	m_BGMVolume = volume;
}
void AudioEngine::SetSFXVolume(const float& volume)
{
	m_SFXVolume = volume;
}

irrklang::ISoundEngine* AudioEngine::GetEngine() const
{
	return m_AudioEngine;
}
float AudioEngine::GetMasterVolume() const
{
	return m_MasterVolume;
}
float AudioEngine::GetBGMVolume() const
{
	return m_BGMVolume;
}
float AudioEngine::GetSFXVolume() const
{
	return m_SFXVolume;
}

// ----------------- Free Memory ----------------- 
void AudioEngine::Free()
{
	m_AudioEngine->drop();
	Singleton::Free();
}

// ----------------- Private Function----------------- 
void AudioEngine::InitSoundEngine()
{
	m_AudioEngine = irrklang::createIrrKlangDevice();

	if (!m_AudioEngine)
	{
		std::cerr << "Error : Failed to Initialize Sound Engine\n";
		exit(EXIT_FAILURE);
	}
}
void AudioEngine::LoadFile(const std::string& filePath, std::map<std::string, AudioSource*>& listContainer)
{
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator(filePath))
	{
		std::string filePathString = (dirEntry.path()).string();
		if (!dirEntry.is_directory())
		{
			std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
			listContainer[filePathString] = m_AudioEngine->addSoundSourceFromFile(filePathString.c_str(), irrklang::ESM_AUTO_DETECT, true);
		}
	}
}