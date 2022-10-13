#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"
#include "ArcantEngine.h"

class Camera
{
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		glm::vec3 m_Up;
		float m_Zoom = 1.0f;

	public:
		Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
		~Camera() {}

		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix(const bool& isZoom);
		void Input(const float& deltaTime);

		// Setter
		void SetPosition(const glm::vec3& position);
		void ResetPosition();
		void SetZoom(const float& zoom);

		// Getter
		glm::vec3 GetPosition() const;
		float GetZoom() const;
};