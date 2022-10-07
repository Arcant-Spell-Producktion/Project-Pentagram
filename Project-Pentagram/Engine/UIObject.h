#pragma once

#include <string>
#include <algorithm>

#include "GameObject.h"
#include "Collector/EngineDataCollector.h"

enum class SlicingType
{
	STRETCH = 0,
	REPEAT
};

class UIObject : public GameObject
{
	protected:
		bool m_IsSlicing = false;
		float m_SlicingBorder = 40.0f;
		float m_SlicingBorderMultiplier = 1.0f;
		SlicingType m_SlicingType = SlicingType::STRETCH;

	public:

		UIObject(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;

		// ----------------- Getter ----------------- 
		bool IsSlicing() const;
		float GetBorderSize() const;
		float GetSlicingBorderMultiplier() const;
		SlicingType GetSlicingType() const;

		// ----------------- Setter ----------------- 
		void SetIsSlicing(const bool& active);
		void SetSlicingBorderSize(const float& slicingBorderSize);
		void SetSlicingBorderMultiplier(const float& slicingBorderMultiplier);
		void SetSlicingType(const SlicingType& slicingType);
};