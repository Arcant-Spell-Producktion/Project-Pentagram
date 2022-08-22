#include "EBO.h"

EBO::EBO()
{
	glGenBuffers(1, &m_ID);
}


void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &m_ID);
}

void EBO::BufferData(GLsizei dataSize, const void* data, GLboolean dynamic)
{
	this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, (dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW));
}

GLuint* EBO::getID()
{
	return &m_ID;
}