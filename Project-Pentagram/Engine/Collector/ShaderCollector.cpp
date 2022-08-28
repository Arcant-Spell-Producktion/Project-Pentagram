#include "ShaderCollector.h"

ShaderCollector::ShaderCollector()
	// Load each shader of object
	: GameObjectShader("Shader/GameObjVertex.shader","Shader/GameObjFragment.shader"),
	  TextShader("Shader/TextVertex.shader", "Shader/TextFragment.shader")
{
	
}


void ShaderCollector::Free()
{

}
