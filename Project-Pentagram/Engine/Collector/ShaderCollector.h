#pragma once

#include "Engine/Renderer/Shader.h"

class ShaderCollector
{
	public:
		// Shader for use with object
		Shader GameObjectShader;
		Shader TextShader;
		Shader ButtonShader;

		ShaderCollector();
		void Free();
};