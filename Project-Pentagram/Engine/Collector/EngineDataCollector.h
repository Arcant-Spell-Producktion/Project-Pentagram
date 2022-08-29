#pragma once

#include "../../Utilities/Singleton.h"

#include "ShaderCollector.h"
#include "FontCollector.h"
#include "TextureCollector.h"

class EngineDataCollector : public Singleton<EngineDataCollector>
{
	private:
		ShaderCollector m_ShaderCollector;
		FontCollector m_FontCollector;
		TextureCollector m_TextureCollector;

	public:
		// Getter
		ShaderCollector* GetShaderCollector();
		FontCollector* GetFontCollector();
		TextureCollector* GetTextureCollector();

		// Free Memory
		void Free();
};