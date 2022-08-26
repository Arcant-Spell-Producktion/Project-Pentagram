#include "FontCollector.h"

FontCollector::FontCollector()
{
	// Initialize FreeType
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "Error : Failed Initialize FreeType Library\n";
		exit(EXIT_FAILURE);
	}

	// Load Font from Asset
	LoadFont("Fonts/ARLRDBD.ttf");
}

void FontCollector::Free()
{
	FT_Done_FreeType(ft);
	Singleton::Free();
}

void FontCollector::LoadFont(const std::string& path)
{
	// Include new Font to FT_FACE
	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face))
	{
		std::cout << "Error : Failed to Load Font\n";
		exit(EXIT_FAILURE);
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// For loop for all possible characters
	for (unsigned char c = 0; c < 128; c++)
	{
		// Load Character
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "Error : Failed to Load Glyph\n";
			continue;
		}

		// Set Texture
		Texture texture;
		texture.SetFontTexture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);
		
		// Set Character and put to std::map
		Character character =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(unsigned int)(face->glyph->advance.x)
		};
		characters[c] = character;
	}

	// Delete FT_FACE
	FT_Done_Face(face);
}