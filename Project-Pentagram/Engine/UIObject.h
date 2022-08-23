#pragma once

#include "GameObject.h"
#include <algorithm>

class UIObject : public GameObject
{
	public:
		// Pointer of Vector (Tracking Current Object in UIObjectList)
		std::vector<UIObject*> *uiList;

		UIObject();
		virtual void Draw(Shader& shader, Camera& camera) override;
		bool onClick();
		bool onHover();
};