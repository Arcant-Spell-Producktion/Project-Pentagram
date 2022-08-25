#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const std::string& objName)
	: GameObject(objName)
{
	tag = GameObjectTag::PARTICLE;

	m_ParticlePool.resize(1000);
	m_PoolIndex = 999;

	curSpawnTime = 0.0f;
	spawnTime = 0.005f;

	// Set Texture
	SetTexture("Sprites/default.png");
}

void ParticleSystem::OnUpdate(const float& dt)
{
	curSpawnTime += dt;
	if (curSpawnTime >= spawnTime)
	{
		this->Emit(this->baseParticle);
		curSpawnTime = 0.0f;
	}

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.active)
		{
			continue;
		}

		if (particle.lifeRemaining <= 0.0f)
		{
			particle.active = false;
			continue;
		}

		particle.lifeRemaining -= dt;
		particle.position += particle.velocity * dt;
		particle.rotation += dt * ROTATION_SPD;
	}
}

void ParticleSystem::Draw(Shader& shader, Camera& camera)
{
	// If object is not-active -> no need to render
	if (!active)
	{
		return;
	}

	shader.Activate();
	shader.setMat4("u_View", camera.getViewMatrix());

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.active)
		{
			continue;
		}

		float life = particle.lifeRemaining / particle.lifeTime;
		glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);
		float size = glm::lerp(particle.sizeBegin, particle.sizeEnd, life);

		// Render
		glm::mat4 model = glm::mat4(1.0f);
		// Update Modelmatrix related to parent Object
		UpdateParentModelMatrix(this, model);

		model *= glm::translate(glm::mat4(1.0f), position);
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), scale);

		model *= glm::translate(glm::mat4(1.0f), glm::vec3(particle.position.x, particle.position.y, 0.0f));
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(particle.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(size, size, 1.0f));

		int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
		int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();
		glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	
		shader.setMat4("u_Model", model);
		shader.setMat4("u_Projection", proj);
		shader.setVec4("u_Color", color);
		texture.Activate(GL_TEXTURE0);
		shader.setInt("u_Texture", 0);

		mesh.Render();
	}

	for (unsigned int idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->Draw(shader, camera);
	}
}

// Implement Texture
void ParticleSystem::SetTexture(const std::string& path)
{
	this->texture.SetTexture(path.c_str(), GL_UNSIGNED_BYTE);
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{

	// RANDOM_FLOAT will random between [0.0f, 1.0f]
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.active = true;
	particle.position = particleProps.position;
	particle.rotation = (RANDOM_FLOAT * 360.0f);

	// Velocity
	particle.velocity = particleProps.velocity;
	particle.velocity.x += particleProps.velocityVariation.x * (RANDOM_FLOAT - 0.5f);
	particle.velocity.y += particleProps.velocityVariation.y * (RANDOM_FLOAT - 0.5f);

	// Color
	particle.colorBegin = particleProps.colorBegin;
	particle.colorEnd = particleProps.colorEnd;

	particle.lifeTime = particleProps.lifeTime;
	particle.lifeRemaining = particleProps.lifeTime;
	particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (RANDOM_FLOAT - 0.5f);
	particle.sizeEnd = particleProps.sizeEnd;

	m_PoolIndex = (--m_PoolIndex >= m_ParticlePool.size() ? m_ParticlePool.size() - 1 : m_PoolIndex);
}