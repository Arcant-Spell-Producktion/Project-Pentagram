#include "AudioGroup.h"

AudioGroup::AudioGroup(const std::string& groupName)
	: m_Name(groupName)
{

}

void AudioGroup::AddAudio(const std::string& filePath, Audio* audio)
{
	m_SubSoundList[filePath] = audio;
}
void AudioGroup::RemoveAudio(const std::string& filePath)
{
	// Handle Error : fileName doesn't exist in this GroupAudio
	// Fixed by check that you have add this fileName to GroupAudio or Mis-Spelling
	ArcantAssert(m_SubSoundList.find(filePath) != m_SubSoundList.end(), filePath + " Doesn't exist in AudioGroup\n");
	
	m_SubSoundList[filePath]->stop();
}
void AudioGroup::SetVolume(const float& volume)
{
	for (auto it = m_SubSoundList.begin(); it != m_SubSoundList.end(); it++)
	{
		it->second->setVolume(volume);
	}
}
void AudioGroup::SetVolume(const std::string& filePath, const float& volume)
{
	// Handle Error : fileName doesn't exist in this GroupAudio
	// Fixed by check that you have add this fileName to GroupAudio or Mis-Spelling
	ArcantAssert(m_SubSoundList.find(filePath) != m_SubSoundList.end(), filePath + " Doesn't exist in AudioGroup\n");

	m_SubSoundList[filePath]->setVolume(volume);
}

Audio* AudioGroup::GetAudio(const std::string & audio)
{
	// Handle Error : fileName doesn't exist in this GroupAudio
	// Fixed by check that you have add this fileName to GroupAudio or Mis-Spelling
	ArcantAssert(m_SubSoundList.find(audio) != m_SubSoundList.end(), audio + " Doesn't exist in AudioGroup\n");

	return m_SubSoundList[audio];
}
std::string AudioGroup::GetGroupName() const
{
	return m_Name;
}
