#pragma once

#include <string>
#include <algorithm>

#include "GameObject.h"
#include "Collector/EngineDataCollector.h"

class UIObject : public GameObject
{
	protected:
		bool m_IsSlicing = false;
		float m_SlicingBorder = 40.0f;

	public:

		UIObject(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;

		// ----------------- Getter ----------------- 
		bool IsSlicing() const;
		float GetBorderSize() const;

		// ----------------- Setter ----------------- 
		void SetIsSlicing(const bool& active);
		void SetSlicingBorderSize(const float& slicingBorderSize);
};