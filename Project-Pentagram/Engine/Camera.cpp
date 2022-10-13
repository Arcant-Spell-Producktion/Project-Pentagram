#include "Camera.h"

Camera::Camera(const glm::vec3& position)
	: m_Position(position)
{
	m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::OnUpdate(const float& dt)
{
	UpdateShake(dt);
}

void Camera::Input(const float& deltaTime)
{
	const float speed = 100.0f;
	if (Input::IsKeyPressed(GLFW_KEY_W))
		m_Position += glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
	if (Input::IsKeyPressed(GLFW_KEY_S))
		m_Position += glm::vec3(0.0f, -1.0f, 0.0f) * speed * deltaTime;
	if (Input::IsKeyPressed(GLFW_KEY_A))
		m_Position += glm::vec3(-1.0f, 0.0f, 0.0f) * speed * deltaTime;
	if (Input::IsKeyPressed(GLFW_KEY_D))
		m_Position += glm::vec3(1.0f, 0.0f, 0.0f) * speed * deltaTime;

}
void Camera::Shake(const float& shakeTime, const int& shakeFrequency, glm::vec2 variation)
{
	this->m_IsShake = true;
	this->m_ShakeTime = shakeTime;
	this->m_ShakeFrequency = shakeFrequency;
	this->m_ShakeVariation = variation;
	this->m_ShakeTimeFrequency = shakeTime / shakeFrequency;
	this->m_ShakeFrequencyCount = 0;
}

// ----------------- Setter Implement -----------------
void Camera::SetPosition(const glm::vec3& position)
{
	this->m_Position = position;
}
void Camera::ResetPosition()
{
	this->m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
}
void Camera::SetZoom(const float& zoom)
{
	this->m_Zoom = zoom;
}

// ----------------- Getter Implement -----------------
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
}
glm::mat4 Camera::GetProjectionMatrix(const bool& isZoom)
{
	Window* window = ArcantEngine::GetInstance()->GetWindow();
	float screenWidth = window->GetWindowWidth() / (isZoom ? m_Zoom : 1.0f);
	float screenHeight = window->GetWindowHeight() / (isZoom ? m_Zoom : 1.0f);
	float near = -1.0f;
	float far = 1.0f;
	return glm::ortho(-screenWidth / 2.0f, screenWidth / 2.0f, -screenHeight / 2.0f, screenHeight / 2.0f, near, far);
}
glm::vec3 Camera::GetPosition() const 
{ 
	return this->m_Position; 
}
float Camera::GetZoom() const 
{ 
	return this->m_Zoom;
}
bool Camera::IsShake() const
{
	return this->m_IsShake;
}
int Camera::GetShakeFrequency() const
{
	return this->m_ShakeFrequency;
}
int Camera::GetShakeFrequencyCount() const
{
	return this->m_ShakeFrequencyCount;
}

// ----------------- Private Function -----------------
void Camera::UpdateShake(const float& dt)
{
	if (!m_IsShake)
	{
		return;
	}

	m_ShakeCurrentTime += dt;
	if (m_ShakeCurrentTime >= m_ShakeTimeFrequency)
	{
		ResetPosition();

		// (float)rand() / RAND_MAX will random from [0, 1]
		float randX = (((float)rand() / RAND_MAX) - 0.5f) * m_ShakeVariation.x;
		float randY = (((float)rand() / RAND_MAX) - 0.5f) * m_ShakeVariation.y;

		m_Position.x = randX;
		m_Position.y = randY;

		m_ShakeFrequencyCount++;
		m_ShakeCurrentTime = 0.0f;

		if (m_ShakeFrequencyCount >= m_ShakeFrequency)
		{
			ResetPosition();
			m_IsShake = false;
		}
	}
}