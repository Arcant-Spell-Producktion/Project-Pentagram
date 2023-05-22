#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.h"
#include "ArcantEngine.h"

class Camera
{
	private:
		glm::vec3 m_Direction;
		glm::vec3 m_Up;
		// ----------------- Camera Zoom Properties -----------------
		float m_Zoom = 1.0f;
		// ----------------- Camera Shake Properties -----------------
		float m_IsShake = false;
		float m_ShakeTime;
		float m_ShakeCurrentTime = 0.0f;
		float m_ShakeTimeFrequency;
		int m_ShakeFrequency;
		int m_ShakeFrequencyCount = 0;
		glm::vec2 m_ShakeVariation;

		void UpdateShake(const float& dt);

	public:
		glm::vec3 position;

		Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
		~Camera() {}

		void OnUpdate(const float& dt);

		void Input(const float& deltaTime);
		// In [shakeTime] (seconds) camera will shake [shakeFrequency] times
		void Shake(const float& shakeTime, const int& shakeFrequency, glm::vec2 variation);

		// ----------------- Setter -----------------
		void ResetPosition();
		void SetZoom(const float& zoom);

		// ----------------- Getter -----------------
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix(const bool& isZoom);
		float GetZoom() const;
		bool IsShake() const;
		int GetShakeFrequency() const;
		int GetShakeFrequencyCount() const;
};