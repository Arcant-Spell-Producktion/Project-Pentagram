#pragma once

#include "GameObject.h"
#include <algorithm>

class UI : public GameObject
{
	private:
	public:
		UI();
		virtual void Draw(Shader& shader, Camera& camera) override;
		bool onClick();
		bool onHover();
};