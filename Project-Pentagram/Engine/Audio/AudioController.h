#pragma once

#include <string>
#include <vector>

#include "AudioEngine.h"
#include "Utilities/Singleton.h"

class BGMAudio
{
	private:
		Audio* m_Audio = nullptr;
	public:
		BGMAudio(Audio* audio)
		: m_Audio(audio)
		{

		}
		~BGMAudio()
		{
			m_Audio->stop();
			m_Audio->drop();
		}

		void Pause()
		{
			m_Audio->setIsPaused(true);
		}
		void Resume()
		{
			m_Audio->setIsPaused(false);
		}
		// ------------------ Setter ------------------
		void SetPlaybackSpeed(const float& speed)
		{
			m_Audio->setPlaybackSpeed(speed);
		}
		void SetVolume(const float& volume)
		{
			m_Audio->setVolume(volume);
		}
		// ------------------ Getter ------------------
		float GetPlaybackSpeed() const
		{
			return m_Audio->getPlaybackSpeed();
		}
		float GetVolume() const
		{
			return m_Audio->getVolume();
		}
		Audio* GetAudio() const
		{
			return m_Audio;
		}
};

class BGMController
{
	private:
		AudioEngine& audioEngine = AudioEngine::GetInstance();

		float m_BGMLocalVolume = 0.0f;
		bool m_IsStartPlay = false;
		
		std::vector<std::string> m_FilepathList;
		std::vector<AudioSource*> m_BGMSourceList;
		std::vector<BGMAudio*> m_BGMAudioList;
		std::vector<float> m_BGMVolumeList;
	
	public:
		BGMController(const std::vector<AudioSource*>& BGMAudioList, const std::vector<float>& volumeList, const std::vector<std::string>& filepathList )
			: m_BGMSourceList(BGMAudioList), m_BGMVolumeList(volumeList), m_FilepathList(filepathList)
		{

		}
		~BGMController()
		{
			for (int idx = 0; idx < m_BGMAudioList.size(); idx++)
			{
				delete m_BGMAudioList[idx];
			}
		}

		void Play()
		{
			m_IsStartPlay = true;

			// If BGM Already played
			if (!m_BGMAudioList.empty()) { return; }

			for (int idx = 0; idx < m_BGMSourceList.size(); idx++)
			{
				const float masterVolume = audioEngine.GetMasterVolume();
				const float bgmVolume = audioEngine.GetBGMVolume();

				AudioSource*& curAudioSource = m_BGMSourceList[idx];
				curAudioSource->setDefaultVolume(m_BGMVolumeList[idx] * m_BGMLocalVolume * masterVolume * bgmVolume);

				Audio* audio = audioEngine.GetBGMEngine()->play2D(curAudioSource, true, false, true, true);
				
				m_BGMAudioList.push_back(new BGMAudio(audio));
			}
		}
		void ChangeVolume(const float& volume)
		{
			m_BGMLocalVolume = volume;
		}
		void OnUpdateVolume()
		{
			const float masterVolume = audioEngine.GetMasterVolume();
			const float bgmVolume = audioEngine.GetBGMVolume();

			for (int idx = 0; idx < m_BGMSourceList.size(); idx++)
			{
				m_BGMAudioList[idx]->SetVolume(m_BGMVolumeList[idx] * m_BGMLocalVolume * masterVolume * bgmVolume);
			}
		}

		bool IsStartPlay() const { return m_IsStartPlay; }

		BGMAudio* operator[](int index)
		{
			return m_BGMAudioList[index];
		}

		std::vector<std::string> GetFilepathList() const
		{
			return m_FilepathList;
		}
};

class AudioController : public Singleton<AudioController>
{
	private:
		AudioEngine& audioEngine = AudioEngine::GetInstance();
		BGMController* m_PrevBGMController = nullptr;
		BGMController* m_BGMController = nullptr;
		std::map<std::string, Audio*> LoopSFX;

		const float fadeTime = 2.0f;
		float m_CurrentTime = 0.0f;

	public:
		void PlaySFX(const std::string& filePath, const float& volume);
		void PlaySFXLoop(const std::string& filePath, const float& volume);
		void StopSFXLoop(const std::string& filePath);
		BGMController* CreateBGM(const std::vector<std::string>& filepathList, const std::vector<float>& volumeList);

		void OnUpdateVolume();
		void OnUpdate(const float& dt);

		// ----------------- Free Memory -----------------
		void Free();
};