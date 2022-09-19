#include "TextureCollector.h"

TextureCollector::TextureCollector()
{
	// Load All Sprites Texture in Folder
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator("Sprites"))
	{
		std::string filePathString = (dirEntry.path()).string();
		std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
		LoadTexture(filePathString);
	}
}

Texture* TextureCollector::GetTexture(const std::string& filePath)
{
	return m_Textures[filePath];
}

void TextureCollector::Free()
{
	for (auto it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		(it->second)->Delete();
		delete it->second;
	}
}

void TextureCollector::LoadTexture(const std::string& filePath)
{
	m_Textures[filePath] = new Texture(filePath.c_str());
}
