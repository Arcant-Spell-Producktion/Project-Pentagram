#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
};

// Array of Square Vertices/Indices
extern Vertex squareVertices[];
extern GLuint squareIndices[];

class Mesh
{
	protected:
		VAO vao;
		VBO vbo;
		EBO ebo;

	public:
		Mesh(const int& animRow, const int& animCol);
		~Mesh();
		void Render();
		void Delete();
};