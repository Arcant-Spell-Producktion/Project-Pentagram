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
		Texture* m_StartGradiantTexture;
		Texture* m_EndGradiantTexture;
		bool m_IsGradiant = false;
		float m_GradiantValue = 0.0f;
		SlicingType m_SlicingType = SlicingType::STRETCH;

	public:

		UIObject(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;

		// ----------------- Getter ----------------- 
		bool IsSlicing() const;
		float GetBorderSize() const;
		float GetSlicingBorderMultiplier() const;
		SlicingType GetSlicingType() const;
		bool IsGradiant() const;
		float GetGradiantValue() const;
		Texture* GetStartGradiantTexture() const;
		Texture* GetEndGradiantTexture() const;

		// ----------------- Setter ----------------- 
		void SetIsSlicing(const bool& active);
		void SetSlicingBorderSize(const float& slicingBorderSize);
		void SetSlicingBorderMultiplier(const float& slicingBorderMultiplier);
		void SetSlicingType(const SlicingType& slicingType);
		void SetIsGradiant(const bool& active);
		void SetGradiantValue(const float& gradiantValue);
		void SetStartGradiantTexture(const std::string& filePath);
		void SetEndGradiantTexture(const std::string& filePath);
};