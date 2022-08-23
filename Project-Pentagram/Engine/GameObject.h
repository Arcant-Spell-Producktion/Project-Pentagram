#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "ArcantEngine.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"

class GameObject
{
	protected:
		Mesh mesh;
		Texture texture;
		int animRow, animCol;
	public:
		bool isActive;
		glm::vec3 position;
		glm::vec3 scale;
		float rotation;
		glm::vec4 color;

		GameObject();
		virtual void Draw(Shader& shader, Camera& camera);
		void UnloadMesh();

		// Texture
		void SetTexture(const char* src);
		// Animation
		void UpdateAnimation(const float& time);
		void SetSpriteSheet(const int& row, const int& col);
};