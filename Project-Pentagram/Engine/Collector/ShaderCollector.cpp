#include "ShaderCollector.h"

ShaderCollector::ShaderCollector()
	// Load each shader of object
	: GameObjectShader("Shader/GameObjVertex.shader","Shader/GameObjFragment.shader"),
	  TextShader("Shader/TextVertex.shader", "Shader/TextFragment.shader"),
	  ButtonShader("Shader/ButtonVertex.shader", "Shader/ButtonFragment.shader")
{
	
}

void ShaderCollector::Free()
{
}
