#pragma once

#include <glad/glad.h>
#include "../stb/stb_image.h"

class Texture
{
private:
	GLuint ID;
public:
	Texture();
	Texture(const char* src, GLenum varType);
	void SetTexture(const char* path, GLenum varType);
	// ---------------------------
	//  SetTexture for Font only
	void SetFontTexture(const GLuint& width, const GLuint& height, const void* data);
	// ---------------------------
	void Activate(GLenum TextureSlot);
	void Bind();
	void UnBind();
	void Delete();
};
