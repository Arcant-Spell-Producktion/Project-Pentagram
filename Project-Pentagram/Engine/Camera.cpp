#include "Camera.h"

Camera::Camera(const glm::vec3& position)
	: m_Position(position)
{
	m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Direction, m_Up);
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

// Setter Implement
void Camera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

// Getter Implement
glm::vec3 Camera::GetPosition() { return m_Position; }