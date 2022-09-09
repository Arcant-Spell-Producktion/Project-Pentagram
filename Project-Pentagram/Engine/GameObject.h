#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <vector>

#include "ArcantEngine.h"
#include "Camera.h"
#include "GameObjectTag.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Collector/EngineDataCollector.h"

class GameObject
{
	protected:
		Mesh m_Mesh;
		Texture* m_Texture;
		bool m_Active;
		unsigned int m_Tag;

		// Animation
		bool m_Animation;
		int m_AnimRow;
		std::vector<int> m_AnimCol;
		int m_MaxAnimCol;
		int m_CurAnimRow = 1, m_CurAnimCol = 1;
		float m_Time = 0.0f;

	public:
		std::string name;
		GameObject* parent;
		std::vector<GameObject*> childList;
		// Transform
		glm::vec3 position;
		glm::vec3 scale;
		float rotation;
		// Color
		glm::vec4 color;

		GameObject(const std::string& objName, const int& animRow = 1, const std::vector<int>& animCol = { 1 });
		virtual ~GameObject();
		virtual void OnUpdate(const float& dt);
		virtual void Draw(Camera& camera, const glm::mat4& parentModel = glm::mat4(1.0f));
		virtual void UnloadMesh();

		void MakeChild(GameObject* gameObj);

		// Getter
		unsigned int GetTag();
		bool isAnimation();
		bool isActive();

		// Setter
		void SetAnimation(const bool& active);
		void SetActive(const bool& active);

		// Texture
		// override in ParticleSystem.h
		virtual void SetTexture(const std::string& path);

		// Animation
		void UpdateAnimation(const float& time, const float& animTime = 0.1f);
		void SetAnimationState(const int& animCol);
};