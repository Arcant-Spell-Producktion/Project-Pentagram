#pragma once

#include "GameObject.h"
#include "Renderer/FontCollector.h"
#include "Renderer/Text.h"
#include <string>
#include <algorithm>

class UIObject : public GameObject
{
	public:
		// Pointer of Vector (Tracking Current Object in UIObjectList)
		std::vector<UIObject*> *uiList;
		Text textUI;

		UIObject();
		virtual void Draw(Shader& shader, Camera& camera) override;
		bool onClick();
		bool onHover();
};