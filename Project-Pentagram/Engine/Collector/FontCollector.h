#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <map>

#include "Engine/Renderer/Texture.h"

#define BASE_FONT_SIZE 72

struct Character
{
	Texture texture;		// ID handle of the glyph texture
	glm::ivec2   size;      // Size of glyph
	glm::ivec2   bearing;   // Offset from baseline to left/top of glyph
	unsigned int advance;   // Horizontal offset to advance to next glyph
};


class FontCollector
{
	private:
		FT_Library ft;
		void LoadFont(const std::string& path);
	public:
		// Collecting each characters' data
		std::map<GLchar, Character> characters;

		FontCollector();
		void Free();
};