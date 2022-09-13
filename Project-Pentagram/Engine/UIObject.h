#pragma once

#include <string>
#include <algorithm>

#include "GameObject.h"
#include "Collector/EngineDataCollector.h"

class UIObject : public GameObject
{
	protected:
		bool m_IsSlicing = false;
		// Frame Border(UI Slicing)
		float m_Border;

	public:

		UIObject(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;

		void SetIsSlicing(const bool& isSlicing);
		void SetBorderSize(const float& borderSize);
		bool IsSlicing();
		float GetBorderSize();
};