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
		Mesh mesh;
	public:
		std::string text;
		TextAlignment textAlignment;
		float fontScale;

		TextObject(const std::string& objName);
		virtual void Draw(Shader& shader, Camera& camera, const glm::mat4& parentModel = glm::mat4(1.0f)) override;
		void RenderText();
		// RenderText in box
		void RenderText(glm::vec3 positionOffset);

};