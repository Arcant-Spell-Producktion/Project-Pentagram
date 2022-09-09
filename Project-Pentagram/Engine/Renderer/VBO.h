#pragma once

#include <glad/glad.h>

class VBO
{
	private:
		GLuint m_ID;
	public:
		VBO();
		~VBO();
		void Bind();
		void UnBind();
		void Delete();
		void BufferData(GLsizei dataSize, const void* data, GLboolean dynamic);
		GLuint* getID();
};