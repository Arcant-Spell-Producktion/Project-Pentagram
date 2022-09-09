#pragma once

#include <string>

#include "Engine/ArcantEngine.h"
#include "Engine/Camera.h"
#include "Engine/UIObject.h"
#include "Engine/Collector/EngineDataCollector.h"
#include "Shader.h"
#include "Mesh.h"

enum class TextAlignment
{
	LEFT = 0,
	MID,
	RIGHT
};

class TextObject : public UIObject
{
	private:
		// Fonts
		std::string m_Fonts;

		// Conatining Glyph Structure
		std::vector<float> m_TextSumX;
		float m_TextMaxY;
		float m_FontScale;

		// Making Text Animation
		int m_CurrentTextIndex;
		float m_CurrentTime;
		float m_RenderTime;
		bool m_SlowRender;

		void CalculateGlyphText(const int& endIndex);
	public:
		std::string text;
		TextAlignment textAlignment;
		float fontSize;
		float lineSpacing;
		glm::vec4 outlineColor;

		TextObject(const std::string& objName);
		virtual void Draw(Camera& camera, const glm::mat4& parentModel = glm::mat4(1.0f)) override;
		virtual void OnUpdate(const float& dt) override;
		virtual void UnloadMesh() override;

		// Setter
		void SetSlowRender(const float& renderTime);
		void SetFonts(const std::string& fontsPath);

		// RenderText in box
		void RenderText(glm::vec3 positionOffset, int start = -1, int end = -1);

};