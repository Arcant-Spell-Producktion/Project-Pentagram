#include "TextureCollector.h"
#include <iostream>

TextureCollector::TextureCollector()
{
}

void TextureCollector::PreLoadResource()
{
	// Load All Sprites Texture in Folder
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator("Sprites"))
	{
		std::string filePathString = (dirEntry.path()).string();
		if (!dirEntry.is_directory())
		{
			std::string fileType = filePathString.substr(filePathString.rfind("."), filePathString.size() - 1);
			if (fileType == ".png" || fileType == ".jpg" || fileType == ".jpeg")
			{
				std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
				LoadTexture(filePathString);
			}
		}
	}
	LoadFile("Sprites/PreLoad");
}

Texture* TextureCollector::GetTexture(const std::string& filePath)
{
	return m_Textures[filePath];
}

void TextureCollector::Free()
{
	for (auto it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		if (it->second)
		{
			(it->second)->Delete();
			delete it->second;
		}
		
	}
}

void TextureCollector::LoadTexture(const std::string& filePath)
{
	if (m_Textures.count(filePath) > 0)
	{
		return;
	}

	std::cout << "Texture Loaded : " << filePath << "\n";
	m_Textures[filePath] = new Texture(filePath.c_str());
}
void TextureCollector::LoadFile(const std::string& filePath)
{
	// Load All Sprites Texture in Folder
	for (const std::filesystem::directory_entry& dirEntry : std::filesystem::recursive_directory_iterator(filePath))
	{
		std::string filePathString = (dirEntry.path()).string();
		if (!dirEntry.is_directory())
		{
			std::string fileType = filePathString.substr(filePathString.rfind("."), filePathString.size() - 1);
			if (fileType == ".png" || fileType == ".jpg" || fileType == ".jpeg")
			{
				std::replace(filePathString.begin(), filePathString.end(), '\\', '/');
				LoadTexture(filePathString);
			}
		}
	}
}
