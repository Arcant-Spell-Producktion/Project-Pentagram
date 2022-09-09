#pragma once

#include <glad/glad.h>

class EBO
{
	private:
		GLuint m_ID;
	public:
		EBO();
		~EBO();
		void Bind();
		void UnBind();
		void Delete();
		void BufferData(GLsizei dataSize, const void* data, GLboolean dynamic);
		GLuint* getID();
};