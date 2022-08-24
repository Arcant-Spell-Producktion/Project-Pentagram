#include "ShaderCollector.h"

ShaderCollector* ShaderCollector::instance = nullptr;

ShaderCollector::ShaderCollector()
	// Load each shader of object
	: GameObjectShader("Shader/GameObjVertex.shader","Shader/GameObjFragment.shader"),
	  TextShader("Shader/TextVertex.shader", "Shader/TextFragment.shader")
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
