#include "EngineDataCollector.h"

void EngineDataCollector::LoadResource()
{
	m_FontCollector.LoadResource();
	AudioEngine::GetInstance().LoadResource();
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
// Free Memory Implement
void EngineDataCollector::Free()
{
	m_ShaderCollector.Free();
	m_FontCollector.Free();
	m_TextureCollector.Free();
	AudioEngine::GetInstance().Free();
}