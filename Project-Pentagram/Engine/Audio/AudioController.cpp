#include "AudioController.h"

void AudioController::PlaySFX(const std::string& filePath, const float& volume)
{
	AudioSource* sfxSource = audioEngine->findSFXAudioSource(filePath);
	const float masterVolume = audioEngine->GetMasterVolume();
	const float sfxVolume = audioEngine->GetSFXVolume();

	sfxSource->setDefaultVolume(volume * masterVolume * sfxVolume);
	
	audioEngine->GetEngine()->play2D(sfxSource);
}
BGMController* AudioController::CreateBGM(const std::vector<std::string>& filepathList, const std::vector<float>& volumeList)
{
	// Convert filePathList -> audioList
	std::vector<AudioSource*> audioList;
	for (const std::string& filepath : filepathList)
	{
		audioList.push_back(audioEngine->findBGMAudioSource(filepath));
	}

	BGMController* bgmController = new BGMController(audioList, volumeList);
	m_BGMControllerList.push_back(bgmController);

	return bgmController;
}

void AudioController::OnUpdate()
{
	for (BGMController* bgmController : m_BGMControllerList)
	{
		bgmController->OnUpdate();
	}
}

// ----------------- Free Memory -----------------
void AudioController::Free()
{
	for (int idx = 0; idx < m_BGMControllerList.size(); idx++) 
	{
		delete m_BGMControllerList[idx];
	}
}