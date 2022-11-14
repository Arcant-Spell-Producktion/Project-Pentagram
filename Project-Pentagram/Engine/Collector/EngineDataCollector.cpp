#include "EngineDataCollector.h"

void EngineDataCollector::LoadResource()
{
	m_FontCollector.LoadResource();
	m_SoundSystem.LoadResource();
	// m_Texture.LoadResource was Loaded in LoadScene.cpp
}

// Getter Implement
ShaderCollector* EngineDataCollector::GetShaderCollector()
{
	return &m_ShaderCollector;
}
FontCollector* EngineDataCollector::GetFontCollector()
{
	return &m_FontCollector;
}
TextureCollector* EngineDataCollector::GetTextureCollector()
{
	return &m_TextureCollector;
}
SoundSystem* EngineDataCollector::GetSoundSystem()
{
	return &m_SoundSystem;
}

// Free Memory Implement
void EngineDataCollector::Free()
{
	m_ShaderCollector.Free();
	m_FontCollector.Free();
	m_TextureCollector.Free();
	m_SoundSystem.FreeEngine();
	Singleton::Free();
}