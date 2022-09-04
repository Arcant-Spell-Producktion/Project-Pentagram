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
	LoadFont("Fonts/BAUHS93.ttf");
}

void FontCollector::Free()
{
	FT_Done_FreeType(ft);
}

std::map<GLchar, Character>* FontCollector::GetFonts(const std::string& fontsPath)
{
	return &fonts[fontsPath];
}

void FontCollector::LoadFont(const std::string& path)
{
	// Init FT_Face & FT_Stroker
	FT_Face face;
	if (FT_New_Face(ft, path.c_str(), 0, &face))
	{
		std::cout << "Error : Failed to Load Font\n";
		exit(EXIT_FAILURE);
	}
	FT_Stroker stroker;
	if (FT_Stroker_New(ft, &stroker))
	{
		std::cout << "Error : Failed to Init Stroke Text"; 
		FT_Done_Face(face);
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, BASE_FONT_SIZE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// For collecting each characters in current Fonts
	std::map<GLchar, Character> characters;

	// For loop for all possible characters
	for (unsigned char c = 0; c < 128; c++)
	{
		// Load Character
		if (FT_Load_Char(face, c, FT_LOAD_NO_BITMAP | FT_LOAD_TARGET_NORMAL))
		{
			std::cout << "Error : Failed to Load Glyph\n";
			continue;
		}

		// Additional Parts
		// -------------------------------------------------------------
		FT_Glyph glyphDescStroke;
		FT_Get_Glyph(face->glyph, &glyphDescStroke);

		static double outlineThickness = 2.0;
		FT_Stroker_Set(stroker, static_cast<FT_Fixed>(outlineThickness * static_cast<float>(1 << 6)), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
		FT_Glyph_Stroke(&glyphDescStroke, stroker, true);

		FT_Glyph_To_Bitmap(&glyphDescStroke, FT_RENDER_MODE_NORMAL, 0, 1);

		FT_BitmapGlyph glyph_bitmap;
		FT_Bitmap* bitmap_stroke = nullptr;
		glyph_bitmap = (FT_BitmapGlyph)glyphDescStroke;
		bitmap_stroke = &glyph_bitmap->bitmap;
		// -------------------------------------------------------------

		unsigned int cx = 0, cy = 0, ox = 0, oy = 0;

		// Set Stroke Text to buffer
		std::vector<unsigned char> buffer;
		cx = bitmap_stroke->width;
		cy = bitmap_stroke->rows;
		ox = glyph_bitmap->left;
		oy = glyph_bitmap->top;

		buffer = std::vector<unsigned char>(cx * cy * 2, 0); // * 2 -> 2 color channels (red and green)
		for (unsigned int i = 0; i < cx * cy; ++i)
		{
			buffer[i * 2 + 1] = bitmap_stroke->buffer[i];      // + 1 -> 2nd color channel
		}
		FT_Done_Glyph(glyphDescStroke);

		// Create Filled Bitmap
		FT_Glyph glyphDescFill;
		FT_Get_Glyph(face->glyph, &glyphDescFill);
		FT_Glyph_To_Bitmap(&glyphDescFill, FT_RENDER_MODE_NORMAL, 0, 1);

		FT_Bitmap* bitmap_fill = nullptr;
		glyph_bitmap = (FT_BitmapGlyph)glyphDescFill;
		bitmap_fill = &glyph_bitmap->bitmap;

		// Assign Filled Bitmap to buffer
		if (bitmap_fill)
		{
			unsigned int cx_fill = bitmap_fill->width;
			unsigned int cy_fill = bitmap_fill->rows;
			unsigned int offset_x = (cx - cx_fill) / 2; // offset because the bitmap my be smaller, 
			unsigned int offset_y = (cy - cy_fill) / 2; // then the former

			for (unsigned int y = 0; y < cy_fill; ++y)
			{
				for (unsigned int x = 0; x < cx_fill; ++x)
				{
					unsigned int i_source = y * cx_fill + x;
					unsigned int i_target = (y + offset_y) * cx + x + offset_x;
					buffer[i_target * 2 + 0] = bitmap_fill->buffer[i_source]; // + 0 -> 1st color channel
				}
			}
		}
		FT_Done_Glyph(glyphDescFill);

		// Set Texture
		Texture texture;
		texture.SetFontTexture(cx, cy, buffer.data());
		
		// Set Character and put to std::map
		Character character =
		{
			texture,
			glm::ivec2(cx, cy),
			glm::ivec2(ox, oy),
			(unsigned int)(face->glyph->advance.x)
		};
		characters[c] = character;
	}

	fonts[path] = characters;

	// Delete FT_FACE
	FT_Done_Face(face);
}