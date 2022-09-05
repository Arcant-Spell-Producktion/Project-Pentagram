#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define RANDOM_FLOAT ((float)rand() / (float)(RAND_MAX))
#define ROTATION_SPD 100.0f

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

#include "ArcantEngine.h"
#include "Camera.h"
#include "GameObject.h"

struct ParticleProps
{
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f), velocityVariation = glm::vec2(0.0f, 0.0f);
	glm::vec4 colorBegin = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), colorEnd = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float sizeBegin = 1.0f, sizeEnd = 1.0f, sizeVariation = 0.0f;
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

			bool active = false;
		};
		std::vector<Particle> m_ParticlePool;
		float curSpawnTime;

	public:
		GLuint m_PoolIndex = 999;
		ParticleProps baseParticle;
		float spawnTime;

		ParticleSystem(const std::string& objName);

		virtual void OnUpdate(const float& dt) override;
		virtual void Draw(Camera &camera, const glm::mat4& parentModel = glm::mat4(1.0f)) override;

		void Emit(const ParticleProps& particleProps);
};