#pragma once

#include <string>

#include "../ArcantEngine.h"
#include "../Camera.h"
#include "FontCollector.h"
#include "ShaderCollector.h"
#include "Shader.h"
#include "Mesh.h"

class Text
{
	private:
		Mesh mesh;
	public:
		glm::vec3 position;
		glm::vec4 color;
		float rotation;
		std::string text;
		float fontSize;
		
		Text();
		void RenderText();

};