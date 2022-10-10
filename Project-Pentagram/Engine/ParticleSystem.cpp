#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const std::string& objName)
	: GameObject(objName)
{
	m_Tag = GameObjectTag::PARTICLE;

	m_PoolIndex = 999;

	m_CurrentSpawnTime = 0.0f;
	spawnTime = 0.005f;
}

void ParticleSystem::OnUpdate(const float& dt)
{
	m_CurrentSpawnTime += dt;
	if (m_CurrentSpawnTime >= spawnTime)
	{
		this->Emit(this->baseParticle);
		m_CurrentSpawnTime = 0.0f;
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
void ParticleSystem::Draw(Camera& camera, glm::mat4 parentModel)
{
	// If object is not-active -> no need to render
	if (!m_IsActive)
	{
		return;
	}
	// Get Particle(GameObject) Shader
	Shader& shader = EngineDataCollector::GetInstance()->GetShaderCollector()->GameObjectShader;

	shader.Activate();

	Window* window = ArcantEngine::GetInstance()->GetWindow();
	int screen_width = window->GetWindowWidth();
	int screen_height = window->GetWindowHeight();
	glm::mat4 proj = glm::ortho(-screen_width / 2.0f, screen_width / 2.0f, -screen_height / 2.0f, screen_height / 2.0f, -10.0f, 10.0f);
	this->m_Texture->Activate(GL_TEXTURE0);
	
	shader.setMat4("u_View", camera.GetViewMatrix());
	shader.setMat4("u_Projection", proj);
	shader.setInt("u_Texture", 0);
	shader.setMat4("u_WindowRatio", glm::scale(glm::mat4(1.0f), glm::vec3(window->GetWindowDiffRatio(), 1.0f)));

	// Render
	glm::mat4 originModel = parentModel;
	originModel *= glm::translate(glm::mat4(1.0f), this->position);
	originModel *= glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	
	// Draw Back Child
	for (unsigned int idx = 0; idx < m_BackRenderedChildList.size(); idx++)
	{
		m_BackRenderedChildList[idx]->Draw(camera, originModel);
	}

	// !!Not Set scale to child -> Messy to encounter with
	
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), this->scale);
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
		glm::mat4 model = originModel * scaleMat;
		model *= glm::translate(glm::mat4(1.0f), glm::vec3(particle.position.x, particle.position.y, 0.0f));
		model *= glm::rotate(glm::mat4(1.0f), glm::radians(particle.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model *= glm::scale(glm::mat4(1.0f), glm::vec3(size, size, 1.0f));

	
		shader.setMat4("u_Model", model);
		shader.setVec4("u_Color", color);

		this->m_Mesh.Render();
	}

	// Draw Front Child
	for (unsigned int idx = 0; idx < m_FrontRenderedChildList.size(); idx++)
	{
		m_FrontRenderedChildList[idx]->Draw(camera, originModel);
	}
}
void ParticleSystem::UnloadMesh()
{
	GameObject::UnloadMesh();
}

void ParticleSystem::Emit(const ParticleProperty& particleProperty)
{

	// RANDOM_FLOAT will random between [0.0f, 1.0f]
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.active = true;
	particle.position = particleProperty.position;
	particle.rotation = (RANDOM_FLOAT * 360.0f);

	// Velocity
	particle.velocity = particleProperty.velocity;
	particle.velocity.x += particleProperty.velocityVariation.x * (RANDOM_FLOAT - 0.5f);
	particle.velocity.y += particleProperty.velocityVariation.y * (RANDOM_FLOAT - 0.5f);

	// Color
	particle.colorBegin = particleProperty.colorBegin;
	particle.colorEnd = particleProperty.colorEnd;

	particle.lifeTime = particleProperty.lifeTime;
	particle.lifeRemaining = particleProperty.lifeTime;
	particle.sizeBegin = particleProperty.sizeBegin + particleProperty.sizeVariation * (RANDOM_FLOAT - 0.5f);
	particle.sizeEnd = particleProperty.sizeEnd;

	this->m_PoolIndex = (--m_PoolIndex >= 1000 ? 1000 - 1 : m_PoolIndex);
}