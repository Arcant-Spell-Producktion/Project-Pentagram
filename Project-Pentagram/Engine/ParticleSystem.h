#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define RANDOM_FLOAT(Min, Max) ((((float)rand() / (float)(RAND_MAX)) * (Max - Min)) + Min)
#define ROTATION_SPD 100.0f

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

#include "ArcantEngine.h"
#include "Camera.h"
#include "GameObject.h"

struct ParticleProperty
{
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 positionVariation = glm::vec2(0.0f, 0.0f);
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f), velocityVariation = glm::vec2(0.0f, 0.0f);
	glm::vec4 colorBegin = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), colorEnd = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	float sizeBegin = 1.0f, sizeEnd = 1.0f, sizeVariation = 0.0f;
	// Rotation (Degree)
	float rotation = 0.0f, rotationVariation = (RANDOM_FLOAT(-1.0, 1.0f) * 180.0f);
	float lifeTime = 1.0f;
};

class ParticleSystem : public GameObject
{
	private:
		struct Particle
		{
			glm::vec2 position;
			glm::vec2 velocity;
			glm::vec4 colorBegin, colorEnd;
			float rotation = 0.0f;
			float sizeBegin, sizeEnd;

			float lifeTime = 1.0f;
			float lifeRemaining = 0.0f;

			int curAnimCol = 1;
			int curAnimRow = 1;

			float animPlayTime = 0.0f;

			bool active = false;
		};
		Particle m_ParticlePool[1000];
		float m_CurrentSpawnTime = 0.0f;
		float spawnTime;
		bool m_IsFixRotation = false;
		bool m_IsGenerate = true;

	public:
		GLuint m_PoolIndex = 999;
		ParticleProperty baseParticle;

		ParticleSystem(const std::string& objName);

		virtual void OnUpdate(const float& dt) override;
		virtual void Draw(Camera &camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;
		virtual void UnloadMesh() override;
		
		void StopGenerate() { m_IsGenerate = false; }
		void StartGenerate() { m_IsGenerate = true; }

		void SetSpawnTime(const float& spawnTime);
		void SetIsFixRotation(const bool& active);
		float GetSpawnTime() const;
		bool IsFixRotation() const;

		void Emit(const ParticleProperty& particleProperty);

		// ----------------- Animation Update ----------------- 
		virtual void UpdateAnimation(const float& deltaTime) override;
};