#include "ShaderCollector.h"

ShaderCollector* ShaderCollector::instance = nullptr;

ShaderCollector::ShaderCollector()
	: GameObjectShader("Shader/GameObjVertex.shader","Shader/GameObjFragment.shader")
{
	
}

ShaderCollector* ShaderCollector::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ShaderCollector();
	}
	return instance;
}

void ShaderCollector::Free()
{
	delete instance;
}
