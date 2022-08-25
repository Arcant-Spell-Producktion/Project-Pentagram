#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

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
		std::string name;
		bool active;
		GameObject* parent;
		std::vector<GameObject*> childList;
		// Transform
		glm::vec3 position;
		glm::vec3 scale;
		float rotation;
		// Color
		glm::vec4 color;

		GameObject(const std::string& objName);
		virtual void OnUpdate(const float& dt);
		virtual void Draw(Shader& shader, Camera& camera);
		void UnloadMesh();

		void MakeChild(GameObject* gameObj);

		// Texture
		// override in ParticleSystem.h
		virtual void SetTexture(const std::string& path);
		// Animation
		void UpdateAnimation(const float& time);
		void SetSpriteSheet(const int& row, const int& col);
};