#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	private:
		GLuint m_ID;
	public:
		VAO();
		void Bind();
		void UnBind();
		void Delete();
		void Attribute(VBO& vbo, GLuint index, GLint size, GLenum varType, GLsizei stride, GLsizei offset);
		GLuint* getID();
};