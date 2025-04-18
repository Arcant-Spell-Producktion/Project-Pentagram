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
		Texture* m_StartGradientTexture;
		Texture* m_EndGradientTexture;
		bool m_IsGradient = false;
		float m_GradientValue = 0.0f;
		bool m_BlockRaycast = false;
		bool m_IsClip = false;
		float m_ClipPercentage = 0.0f;
		SlicingType m_SlicingType = SlicingType::STRETCH;

	public:

		UIObject(const std::string& objName);
		virtual void Draw(Camera& camera, glm::mat4 parentModel = glm::mat4(1.0f)) override;

		// ----------------- Getter ----------------- 
		bool IsSlicing() const;
		float GetBorderSize() const;
		float GetSlicingBorderMultiplier() const;
		SlicingType GetSlicingType() const;
		bool IsGradient() const;
		float GetGradientValue() const;
		Texture* GetStartGradientTexture() const;
		Texture* GetEndGradientTexture() const;
		bool IsBlockRaycast() const;

		// ----------------- Setter ----------------- 
		void SetIsSlicing(const bool& active);
		void SetSlicingBorderSize(const float& slicingBorderSize);
		void SetSlicingBorderMultiplier(const float& slicingBorderMultiplier);
		void SetSlicingType(const SlicingType& slicingType);
		void SetIsGradient(const bool& active);
		void SetGradientValue(const float& gradiantValue);
		void SetStartGradientTexture(const std::string& filePath);
		void SetEndGradientTexture(const std::string& filePath);
		void SetBlockRaycast(const bool& active);
		void SetIsClip(const bool& active);
		void SetClipPercentage(const float& percent);
};