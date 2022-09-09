#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const std::string& objName)
	: GameObject(objName)
{
	m_Tag = GameObjectTag::PARTICLE;

	m_PoolIndex = 999;

	curSpawnTime = 0.0f;
	spawnTime = 0.005f;
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

void ParticleSystem::Draw(Camera& camera, const glm::mat4& parentModel)
{
	// If object is not-active -> no need to render
	if (!m_Active)
	{
		return;
	}
	// Get Particle(GameObject) Shader
	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->GameObjectShader;

	shader.Activate();
	shader.setMat4("u_View", camera.getViewMatrix());
	m_Texture->Activate(GL_TEXTURE0);
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	shader.setMat4("u_Projection", proj);
	shader.setInt("u_Texture", 0);

	// Render
	glm::mat4 originModel = parentModel;
	originModel *= glm::translate(glm::mat4(1.0f), position);
	originModel *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	originModel *= glm::scale(glm::mat4(1.0f), scale);
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.active)
		{
			continue;
		}

		float life = particle.lifeRemaining / particle.lifeTime;
		glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);
		float size = glm::lerp(particle.sizeBegin, particle.sizeEnd, life);

		if (color.a <= 0.0f)
		{
			continue;
		}
		glm::mat4 model = originModel;
		model *= glm::translate(glm::mat4(1.0f), glm::vec3(particle.position.x, particle.position.y, 0.0f));
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(particle.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(size, size, 1.0f));

	
		shader.setMat4("u_Model", model);
		shader.setVec4("u_Color", color);

		m_Mesh.Render();
	}

	for (unsigned int idx = 0; idx < childList.size(); idx++)
	{
		childList[idx]->Draw(camera, originModel);
	}
}

void ParticleSystem::UnloadMesh()
{
	GameObject::UnloadMesh();
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

	m_PoolIndex = (--m_PoolIndex >= 1000 ? 1000 - 1 : m_PoolIndex);
}