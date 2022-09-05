#include "TextureCollector.h"

TextureCollector::TextureCollector()
{
	// Load All Sprites Texture
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator("Sprites"))
	{
		std::string filePathString = (dirEntry.path()).string();
		std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
		LoadTexture(filePathString);
	}
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
