#pragma once

#include "../Renderer/Shader.h"

class ShaderCollector
{
	public:
		// Shader for use with object
		Shader GameObjectShader;
		Shader TextShader;

		ShaderCollector();
		void Free();
};