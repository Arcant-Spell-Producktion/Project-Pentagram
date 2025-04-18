#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
	InitSoundEngine();
}
void AudioEngine::LoadResource()
{
	// Load All BGM
	LoadFile(m_BGMEngine, "Audio/BGM", m_BGMSourceList);
	// Load All SFX
	LoadFile(m_SFXEngine, "Audio/SFX", m_SFXSourceList);
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

irrklang::ISoundEngine* AudioEngine::GetBGMEngine() const
{
	return m_BGMEngine;
}
irrklang::ISoundEngine* AudioEngine::GetSFXEngine() const
{
	return m_SFXEngine;
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
	m_BGMEngine->drop();
	m_SFXEngine->drop();
	Singleton::Free();
}

// ----------------- Private Function----------------- 
void AudioEngine::InitSoundEngine()
{
	m_BGMEngine = irrklang::createIrrKlangDevice();
	m_SFXEngine = irrklang::createIrrKlangDevice();

	if (!m_BGMEngine || !m_SFXEngine)
	{
		std::cerr << "Error : Failed to Initialize Sound Engine\n";
		exit(EXIT_FAILURE);
	}
}
void AudioEngine::LoadFile(irrklang::ISoundEngine* engine, const std::string& filePath, std::map<std::string, AudioSource*>& listContainer)
{
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator(filePath))
	{
		std::string filePathString = (dirEntry.path()).string();
		if (!dirEntry.is_directory())
		{
			std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
			listContainer[filePathString] = engine->addSoundSourceFromFile(filePathString.c_str(), irrklang::ESM_AUTO_DETECT, true);
		}
	}
}