#pragma once

#include <assert.h>
#include <string>
#include <map>

#include "Engine/Renderer/Texture.h"

class TextureCollector
{
	private:
		std::map<std::string, Texture*> textures;
	public:
		TextureCollector();
		Texture* GetTexture(const std::string& name);
		void Free();
};