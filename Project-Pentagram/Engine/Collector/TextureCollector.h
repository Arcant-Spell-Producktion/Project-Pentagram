#pragma once

#include <assert.h>
#include <filesystem>
#include <algorithm>
#include <string>
#include <map>

#include "Engine/Renderer/Texture.h"

class TextureCollector
{
	private:
		std::map<std::string, Texture*> m_Textures;

		void LoadTexture(const std::string& filePath);
		void LoadFile(const std::string& filePath);

	public:
		TextureCollector();
		void PreLoadResource();
		void LoadResource();

		Texture* GetTexture(const std::string& filePath);
		
		void Free();
};