#include "ShaderCollector.h"

ShaderCollector::ShaderCollector()
	// Load each shader of object
	: GameObjectShader("Shader/GameObjVertex.shader","Shader/GameObjFragment.shader"),
	  TextShader("Shader/TextVertex.shader", "Shader/TextFragment.shader"),
	  UISlicingShader("Shader/UISlicingVertex.shader", "Shader/UISlicingFragment.shader"),
	  GradiantShader("Shader/GradiantVertex.shader", "Shader/GradiantFragment.shader")
{
	
}

void ShaderCollector::Free()
{
}
