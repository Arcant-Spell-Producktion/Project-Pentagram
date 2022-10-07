#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Engine/stb/stb_image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>

class Texture
{
	private:
		GLuint ID;
    
		int m_ImageRow;
		std::vector<int> m_ImageColumn;
		int m_MaxImageColumn;

		GLuint m_Width;
		GLuint m_Height;
	public:
		Texture();
		Texture(const char* src);
		void SetTexture(const char* path);
		void ReadMeta(const std::string& filePath);
		// ---------------------------
		//  SetTexture for Font only
		void SetFontTexture(const GLuint& width, const GLuint& height, const void* data);
		// ---------------------------
		void Activate(GLenum TextureSlot);
		void Bind();
		void UnBind();
		void Delete();

		// ----------------- Getter -----------------
		glm::ivec2 GetImageSize() const;
		GLuint GetImageWidth() const;
		GLuint GetImageHeight() const;
		int GetImageRow() const;
		std::vector<int> GetImageColumn() const;
		int GetMaxImageColumn() const;
};
