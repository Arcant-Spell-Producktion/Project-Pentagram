#include "VBO.h"

// Constructor -> Generate VBO
VBO::VBO()
{
	glGenBuffers(1, &m_ID);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Delete VBO via ID
void VBO::Delete()
{
	glDeleteBuffers(1, &m_ID);
}

// Bind Buffer and Specific that Buffer
void VBO::BufferData(GLsizei dataSize, const void* data, GLboolean dynamic)
{
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, (dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

// Get VBO ID
GLuint* VBO::getID()
{
	return &m_ID;
}