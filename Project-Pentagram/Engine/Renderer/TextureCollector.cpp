#include "TextureCollector.h"

TextureCollector::TextureCollector()
{
	textures["Sprites/awesomeface.png"] = new Texture("Sprites/awesomeface.png");
	textures["Sprites/default.png"] = new Texture("Sprites/default.png");
}

Texture* TextureCollector::GetTexture(const std::string& name)
{
	return textures[name];
}

void TextureCollector::Free()
{
	for (auto it = textures.begin(); it != textures.end(); it++)
	{
		(it->second)->Delete();
		delete it->second;
	}
	Singleton::Free();
}