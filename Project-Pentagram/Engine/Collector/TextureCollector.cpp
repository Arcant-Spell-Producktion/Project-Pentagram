#include "TextureCollector.h"
#include <iostream>


TextureCollector::TextureCollector()
{
	LoadTexture("Sprites/awesomeface.png");
	LoadTexture("Sprites/default.png");
	LoadTexture("Sprites/player_fire_idle.png");
	LoadTexture("Sprites/Fire_Mage.png");
	LoadTexture("Sprites/character_minion_idle.png");
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
}

void TextureCollector::LoadTexture(const std::string& path)
{
	textures[path] = new Texture(path.c_str());
}
