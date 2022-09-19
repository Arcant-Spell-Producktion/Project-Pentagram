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
		// ----------------- Rendering -----------------
		Mesh m_Mesh;
		Texture* m_Texture;
		bool m_IsActive;
		unsigned int m_Tag;

		// ----------------- Animation -----------------
		bool m_IsAnimationPlaying;
		bool m_IsAnimationObject;
		bool m_IsSpriteSheet;

		int m_AnimationRow;
		std::vector<int> m_AnimationColumn;
		
		int m_MaxAnimationColumn;
		int m_CurrentAnimationRow = 1, m_CurrentAnimationColumn = 1;
		float m_AnimationPlayTime = 0.1f;
		float m_CurrentPlayTime = 0.0f;

		// ----------------- Child -----------------
		std::vector<GameObject*> m_FrontRenderedChildList;
		std::vector<GameObject*> m_BackRenderedChildList;

	public:
		// ----------------- General ----------------- 
		std::string name;
		GameObject* parent;
		// ----------------- Transform ----------------- 
		glm::vec3 position;
		glm::vec3 scale;
		float rotation;
		// ----------------- Color ----------------- 
		glm::vec4 color;

		GameObject(const std::string& objName, const int& animRow = 1, const std::vector<int>& animCol = { 1 });
		virtual ~GameObject();
		virtual void OnUpdate(const float& dt);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f));
		virtual void UnloadMesh();


		// ----------------- Getter ----------------- 
		// Rendering
		unsigned int GetTag() const;
		bool IsActive() const;
		Texture* GetTexture() const;
		// Animation
		int GetCurrentAnimationRow() const;
		int GetCurrentAnimationColumn() const;
		glm::ivec2 GetCurrentAnimationIndex() const;
		int GetAnimationRow() const;
		int GetAnimationColumn(const int& row) const;
		float GetAnimationPlayTime() const;
		float GetCurrentAnimationPlayTime() const;
		bool IsAnimationObject() const;
		bool IsAnimationPlaying() const;
		bool IsSpriteSheet() const;

		// ----------------- Setter ----------------- 
		// Rendering
		void SetActive(const bool& active);
		void SetChildRenderFront(GameObject* gameObj);
		void SetChildRenderBack(GameObject* gameObj);
		// Animation
		void SetIsAnimationObject(const bool& active);
		void SetAnimationSpriteByIndex(const int& animationRow, const int& animationColumn);
		void SetSpriteByIndex(const int& row, const int& column);
		void SetAnimationPlayTime(const float& animationPlayTime);
		// Texture
		// override in ParticleSystem.h
		virtual void SetTexture(const std::string& filePath);
		virtual void SetTexture(Texture* texture);


		// ----------------- Animation Update ----------------- 
		void UpdateAnimation(const float& deltaTime);
};