#include "Camera.h"

Camera::Camera(const glm::vec3& position)
	: m_position(position)
{
	m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::Input(const float& deltaTime)
{
	const float speed = 100.0f;
	if (Input::IsKeyPressed(GLFW_KEY_W))
		m_position += glm::vec3(0.0f, 1.0f, 0.0f) * speed * deltaTime;
	if (Input::IsKeyPressed(GLFW_KEY_S))
		m_position += glm::vec3(0.0f, -1.0f, 0.0f) * speed * deltaTime;
	if (Input::IsKeyPressed(GLFW_KEY_A))
		m_position += glm::vec3(-1.0f, 0.0f, 0.0f) * speed * deltaTime;
	if (Input::IsKeyPressed(GLFW_KEY_D))
		m_position += glm::vec3(1.0f, 0.0f, 0.0f) * speed * deltaTime;

}

// Setter Implement
void Camera::SetPosition(const glm::vec3& position)
{
	m_position = position;
}

// Getter Implement
glm::vec3 Camera::getPosition() { return m_position; }