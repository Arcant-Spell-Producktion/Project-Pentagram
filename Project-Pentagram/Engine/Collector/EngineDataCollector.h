#pragma once

#include "Utilities/Singleton.h"

#include "Engine/Collector/ShaderCollector.h"
#include "Engine/Collector/FontCollector.h"
#include "Engine/Collector/TextureCollector.h"
#include "Engine/Audio/AudioEngine.h"

class EngineDataCollector : public Singleton<EngineDataCollector>
{
	private:
		ShaderCollector m_ShaderCollector;
		FontCollector m_FontCollector;
		TextureCollector m_TextureCollector;

	public:
		void LoadResource();

		// Getter
		ShaderCollector* GetShaderCollector();
		FontCollector* GetFontCollector();
		TextureCollector* GetTextureCollector();

		// Free Memory
		void Free();
};