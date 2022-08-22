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
	void SetTexture(const char* src, GLenum varType);
	void Activate(GLenum TextureSlot);
	void Bind();
	void UnBind();
	void Delete();
};
