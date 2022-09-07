#include "AudioGroup.h"

AudioGroup::AudioGroup(const std::string& groupName)
	: m_Name(groupName)
{

}

void AudioGroup::AddAudio(const std::string& fileName, Audio* audio)
{
	m_SubSoundList[fileName] = audio;
}

void AudioGroup::RemoveAudio(const std::string& fileName)
{
	m_SubSoundList[fileName]->stop();
}

void AudioGroup::SetVolume(const float& volume)
{
	for (auto it = m_SubSoundList.begin(); it != m_SubSoundList.end(); it++)
	{
		it->second->setVolume(volume);
	}
}

void AudioGroup::SetVolume(const std::string& fileName, const float& volume)
{
	m_SubSoundList[fileName]->setVolume(volume);
}

Audio* AudioGroup::GetAudio(const std::string & audio)
{
	return m_SubSoundList[audio];
}
