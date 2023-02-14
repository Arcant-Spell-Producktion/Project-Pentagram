#include "AudioController.h"

void AudioController::PlaySFX(const std::string& filePath, const float& volume)
{
	AudioSource* sfxSource = audioEngine->findSFXAudioSource(filePath);
	const float masterVolume = audioEngine->GetMasterVolume();
	const float sfxVolume = audioEngine->GetSFXVolume();

	sfxSource->setDefaultVolume(volume * masterVolume * sfxVolume);
	
	audioEngine->GetEngine()->play2D(sfxSource);
}
void AudioController::PlaySFXLoop(const std::string& filePath, const float& volume)
{
	AudioSource* sfxSource = audioEngine->findSFXAudioSource(filePath);
	const float masterVolume = audioEngine->GetMasterVolume();
	const float sfxVolume = audioEngine->GetSFXVolume();

	sfxSource->setDefaultVolume(volume * masterVolume * sfxVolume);

	Audio* curSFX = audioEngine->GetEngine()->play2D(sfxSource, true, false, true, false);
	LoopSFX[filePath] = curSFX;
}
void AudioController::StopSFXLoop(const std::string& filePath)
{
	if (LoopSFX[filePath] == nullptr) { return; }

	LoopSFX[filePath]->stop();
	LoopSFX[filePath]->drop();
	LoopSFX[filePath] = nullptr;
}

BGMController* AudioController::CreateBGM(const std::vector<std::string>& filepathList, const std::vector<float>& volumeList)
{
	if (m_BGMController != nullptr)
	{
		if (m_BGMController->GetFilepathList() == filepathList)
		{
			return m_BGMController;
		}
		else
		{
			delete m_BGMController;
			m_BGMController = nullptr;
		}
	}

	// Convert filePathList -> audioList
	std::vector<AudioSource*> audioList;
	for (const std::string& filepath : filepathList)
	{
		audioList.push_back(audioEngine->findBGMAudioSource(filepath));
	}

	m_BGMController = new BGMController(audioList, volumeList, filepathList);

	return m_BGMController;
}

void AudioController::OnUpdate()
{
	if (m_BGMController == nullptr) { return; }
	m_BGMController->OnUpdate();
}

// ----------------- Free Memory -----------------
void AudioController::Free()
{
	if (m_BGMController == nullptr) { return; }
	delete m_BGMController;
}