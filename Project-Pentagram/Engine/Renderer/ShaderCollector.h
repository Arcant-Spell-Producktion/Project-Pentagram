#pragma once

#include "Shader.h"

class ShaderCollector
{
	private:
		static ShaderCollector* instance;

	public:
		// Shader for use with object
		Shader GameObjectShader;
		Shader TextShader;

		ShaderCollector();
		static ShaderCollector* GetInstance();
		void Free();
};