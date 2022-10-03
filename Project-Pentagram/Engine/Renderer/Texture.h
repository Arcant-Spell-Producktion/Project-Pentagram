#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Engine/stb/stb_image.h"

#include <assert.h>

class Texture
{
	private:
		GLuint ID;
		
		GLuint m_Width;
		GLuint m_Height;
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

		// ----------------- Getter ----------------- 
		glm::vec2 GetImageSize() const;
		GLuint GetImageWidth() const;
		GLuint GetImageHeight() const;
};
