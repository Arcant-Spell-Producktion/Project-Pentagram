#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"

class Camera
{
	private:
		glm::vec3 m_position;
		glm::vec3 m_direction;
		glm::vec3 m_up;

	public:
		Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
		~Camera() {}

		glm::mat4 getViewMatrix();
		void Input(const float& deltaTime);

		// Setter
		void SetPosition(const glm::vec3& position);

		// Getter
		glm::vec3 getPosition();
};