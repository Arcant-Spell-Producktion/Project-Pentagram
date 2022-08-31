#include "TextureCollector.h"
#include <iostream>


TextureCollector::TextureCollector()
{
	textures["Sprites/awesomeface.png"] = new Texture("Sprites/awesomeface.png");
	textures["Sprites/default.png"] = new Texture("Sprites/default.png");
	textures["Sprites/player_fire_idle.png"] = new Texture("Sprites/player_fire_idle.png");
	textures["Sprites/Fire_Mage.png"] = new Texture("Sprites/Fire_Mage.png");
	textures["Sprites/character_minion_idle.png"] = new Texture("Sprites/character_minion_idle.png");
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