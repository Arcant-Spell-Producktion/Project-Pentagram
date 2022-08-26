#pragma once

#include <string>
#include <map>

#include "../../Utilities/Singleton.h"
#include "Texture.h"

class TextureCollector : public Singleton<TextureCollector>
{
	private:
		std::map<std::string, Texture*> textures;
	public:
		TextureCollector();
		Texture* GetTexture(const std::string& name);
		void Free();
};