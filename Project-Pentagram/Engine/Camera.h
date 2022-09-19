#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"

class Camera
{
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		glm::vec3 m_Up;

	public:
		Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
		~Camera() {}

		glm::mat4 GetViewMatrix();
		void Input(const float& deltaTime);

		// Setter
		void SetPosition(const glm::vec3& position);

		// Getter
		glm::vec3 GetPosition();
};