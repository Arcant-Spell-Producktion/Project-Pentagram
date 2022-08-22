#pragma once

#include "Shader.h"

class ShaderCollector
{
	private:
		static ShaderCollector* instance;

	public:
		Shader GameObjectShader;

		ShaderCollector();
		static ShaderCollector* GetInstance();
		void Free();
};