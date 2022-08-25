#pragma once

#include "GameObject.h"
#include "Renderer/FontCollector.h"
#include <string>
#include <algorithm>

class UIObject : public GameObject
{
	public:
		UIObject(const std::string& objName);
		virtual void Draw(Shader& shader, Camera& camera) override;
};