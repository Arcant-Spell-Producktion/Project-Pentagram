#include "VAO.h"

// Constructor -> Generate VAO
VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);
}

void VAO::Bind()
{
	glBindVertexArray(m_ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

// Delete Vertex Array via ID
void VAO::Delete()
{
	glDeleteVertexArrays(1, &m_ID);
}

// Bind VBO and Specific Data(AttribPointer) of that VBO
void VAO::Attribute(VBO& vbo, GLuint index, GLint size, GLenum varType, GLsizei stride, GLsizei offset)
{
	vbo.Bind();
	glVertexAttribPointer(index, size, varType, GL_FALSE, stride, (const void*)offset);
	glEnableVertexAttribArray(index);
	vbo.UnBind();
}

// Get VAO ID
GLuint* VAO::getID()
{
	return &m_ID;
}