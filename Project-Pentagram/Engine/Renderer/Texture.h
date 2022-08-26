#pragma once

#include <glad/glad.h>
#include "../stb/stb_image.h"

class Texture
{
private:
	GLuint ID;
public:
	Texture();
	Texture(const char* src);
	void SetTexture(const char* path);
	// ---------------------------
	//  SetTexture for Font only
	void SetFontTexture(const GLuint& width, const GLuint& height, const void* data);
	// ---------------------------
	void Activate(GLenum TextureSlot);
	void Bind();
	void UnBind();
	void Delete();
};
