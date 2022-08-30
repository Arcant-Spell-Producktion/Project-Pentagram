#include "Mesh.h"

Vertex squareVertices[] =
{
	Vertex{ glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f) },		// Top-Right
	Vertex{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 1.0f) },		// Bottom-Right
	Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 1.0f) },		// Bottom-Left
	Vertex{ glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f) }		// Top-Left
};

GLuint squareIndices[] =
{
	0, 1, 3,	// Top-Right Section
	1, 2, 3		// Bottom-Left Section
};

Mesh::Mesh()
{
	vao.Bind();
	vbo.BufferData(sizeof(squareVertices), squareVertices, false);
	ebo.BufferData(sizeof(squareIndices), squareIndices, false);

	vao.Attribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	vao.Attribute(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), 3 * sizeof(float));

	vbo.UnBind();
	ebo.UnBind();
}

Mesh::Mesh(const int& animRow, const int& animCol)
{
	Vertex squareAnimVertices[] =
	{
		Vertex{ glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f / animCol, 0.0f) },					// Top-Right
		Vertex{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f / animCol, 1.0f / animRow) },		// Bottom-Right
		Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 1.0f / animRow) },				// Bottom-Left
		Vertex{ glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f) }							// Top-Left
	};

	vao.Bind();
	vbo.BufferData(sizeof(squareAnimVertices), squareAnimVertices, false);
	ebo.BufferData(sizeof(squareIndices), squareIndices, false);

	vao.Attribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	vao.Attribute(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), 3 * sizeof(float));

	vbo.UnBind();
	ebo.UnBind();
}

void Mesh::Render()
{
	vao.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, squareIndices);
}

void Mesh::Delete()
{
	// Delete All of Buffers
	glDeleteVertexArrays(1, vao.getID());
	glDeleteBuffers(1, vbo.getID());
	glDeleteBuffers(1, ebo.getID());
}