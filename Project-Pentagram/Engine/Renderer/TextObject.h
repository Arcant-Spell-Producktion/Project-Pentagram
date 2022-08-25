#pragma once

#include <string>

#include "../ArcantEngine.h"
#include "../Camera.h"
#include "../UIObject.h"
#include "FontCollector.h"
#include "ShaderCollector.h"
#include "Shader.h"
#include "Mesh.h"

enum TextAlignment
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
		void RenderText();
		// RenderText in box
		void RenderText(glm::vec3 positionOffset);

};