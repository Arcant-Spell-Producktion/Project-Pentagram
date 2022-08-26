#pragma once

#include "Shader.h"
#include "../../Utilities/Singleton.h"

class ShaderCollector : public Singleton<ShaderCollector>
{
	public:
		// Shader for use with object
		Shader GameObjectShader;
		Shader TextShader;

		ShaderCollector();
		void Free();
};