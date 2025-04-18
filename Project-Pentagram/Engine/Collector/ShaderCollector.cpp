#include "ShaderCollector.h"

ShaderCollector::ShaderCollector()
	// Load each shader of object
	: GameObjectShader("Shader/GameObjVertex.shader","Shader/GameObjFragment.shader"),
	  TextShader("Shader/TextVertex.shader", "Shader/TextFragment.shader"),
	  UISlicingShader("Shader/UISlicingVertex.shader", "Shader/UISlicingFragment.shader"),
	  GradientShader("Shader/GradientVertex.shader", "Shader/GradientFragment.shader")
{
	
}

void ShaderCollector::Free()
{
}
