#pragma once

#include "Engine/Renderer/Shader.h"

class ShaderCollector
{
	public:
		// Shader for use with object
		Shader GameObjectShader;
		Shader TextShader;
		Shader UISlicingShader;
		Shader GradientShader;

		ShaderCollector();
		void Free();
};