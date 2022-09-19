#include "GameScene.h"

GameScene::~GameScene()
{

}

// ----------------- Creating Object ----------------- 
GameObject* GameScene::CreateGameObject(const std::string& objName, const int& animRow, const std::vector<int>& animCol)
{
	GameObject* obj = nullptr;
	if (objName == "")
	{
		obj = new GameObject("GameObject_" + std::to_string(objectsList.size()), animRow, animCol);
	}
	else
	{
		obj = new GameObject(objName, animRow, animCol);
	}

	objectsList.push_back(obj);
	return obj;
}
ParticleSystem* GameScene::CreateParticle(ParticleProperty& particleProperty)
{
	ParticleSystem* particle = new ParticleSystem("Particle_" + std::to_string(objectsList.size()));
	particle->baseParticle = particleProperty;
	objectsList.push_back(particle);
	return particle;
}
ParticleSystem* GameScene::CreateParticle(const std::string& objName, ParticleProperty& particleProperty)
{
	ParticleSystem* particle = new ParticleSystem(objName);
	particle->baseParticle = particleProperty;
	objectsList.push_back(particle);
	return particle;
}
UIObject* GameScene::CreateUIObject(const std::string& objName)
{
	UIObject* ui = nullptr;
	if (objName == "")
	{
		ui = new UIObject("UI_" + std::to_string(uiObjectsList.size()));
	}
	else
	{
		ui = new UIObject(objName);
	}

	uiObjectsList.push_back(ui);
	return ui;
}
TextObject* GameScene::CreateTextObject(const std::string& objName)
{
	TextObject* textObj = nullptr;
	if (objName == "")
	{
		textObj = new TextObject("TextObject_" + std::to_string(uiObjectsList.size()));
	}
	else
	{
		textObj = new TextObject(objName);
	}
	uiObjectsList.push_back(textObj);
	return textObj;

}
Button* GameScene::CreateButton(const std::string& objName)
{
	Button* button = nullptr;
	if (objName == "")
	{
		button = new Button("Button_" + std::to_string(uiObjectsList.size()));
	}
	else
	{
		button = new Button(objName);
	}
	uiObjectsList.push_back(button);
	buttonObjectsList.push_back(button);
	return button;
}
Slider* GameScene::CreateSlider(const std::string& objName)
{
	Slider* slider = nullptr;
	if (objName == "")
	{
		slider = new Slider("Slider_" + std::to_string(uiObjectsList.size()));
	}
	else
	{
		slider = new Slider(objName);
	}
	uiObjectsList.push_back(slider);

	Button* button = CreateButton("Button_" + (objName == "" ? "Sldier_" + std::to_string(uiObjectsList.size()) : objName));
	slider->InitButton(button);

	return slider;
}

// ----------------- Button Events ----------------- 

glm::vec3 GameScene::FindButtonParentPosition(const Button* button)
{
	if (button->parent == nullptr)
	{
		return button->position;
	}
	else
	{
		glm::vec3 curPos = button->position;
		GameObject* curObj = button->parent;
		while (curObj != nullptr)
		{
			curPos += curObj->position;
			curObj = curObj->parent;
		}
		return curPos;
	}
}

void GameScene::UpdateButtonOnClick()
{
	if (!Input::IsKeyEndPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		return;
	}
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();

	glm::vec2 windowScale = ArcantEngine::GetInstance()->GetWindow()->GetWindowRatio();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	for (int idx = buttonObjectsList.size() - 1; idx >= 0; idx--)
	{
		Button* curObj = buttonObjectsList[idx];
		glm::vec3 finalPos = FindButtonParentPosition(curObj);

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->IsActive())
		{
			continue;
		}
		float left = (finalPos.x - (curObj->scale.x / 2.0f)) * windowScale.x;
		float right = (finalPos.x + (curObj->scale.x / 2.0f)) * windowScale.x;
		float top = (finalPos.y + (curObj->scale.y / 2.0f)) * windowScale.y;
		float bottom = (finalPos.y - (curObj->scale.y / 2.0f)) * windowScale.y;

		if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			curObj->onClick(curObj);
			return;
		}
	}
}
void GameScene::UpdateButtonOnHover()
{
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	glm::vec2 windowScale = ArcantEngine::GetInstance()->GetWindow()->GetWindowRatio();

	for (int idx = buttonObjectsList.size() - 1; idx >= 0; idx--)
	{
		Button* curObj = buttonObjectsList[idx];
		glm::vec3 finalPos = FindButtonParentPosition(curObj);

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->IsActive())
		{
			continue;
		}
		float left = (finalPos.x - (curObj->scale.x / 2.0f)) * windowScale.x;
		float right = (finalPos.x + (curObj->scale.x / 2.0f)) * windowScale.x;
		float top = (finalPos.y + (curObj->scale.y / 2.0f)) * windowScale.y;
		float bottom = (finalPos.y - (curObj->scale.y / 2.0f)) * windowScale.y;

		if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			curObj->onHover(curObj);
			return;
		}
		else
		{
			curObj->unHover(curObj);
		}
	}
}
void GameScene::UpdateButtonOnPress()
{
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	glm::vec2 windowScale = ArcantEngine::GetInstance()->GetWindow()->GetWindowRatio();

	for (int idx = buttonObjectsList.size() - 1; idx >= 0; idx--)
	{
		Button* curObj = buttonObjectsList[idx];
		glm::vec3 finalPos = FindButtonParentPosition(curObj);

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->IsActive())
		{
			continue;
		}
		float left = (finalPos.x - (curObj->scale.x / 2.0f)) * windowScale.x;
		float right = (finalPos.x + (curObj->scale.x / 2.0f)) * windowScale.x;
		float top = (finalPos.y + (curObj->scale.y / 2.0f)) * windowScale.y;
		float bottom = (finalPos.y - (curObj->scale.y / 2.0f)) * windowScale.y;

		if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				curObj->onPress(curObj);
				return;
			}
			else if(!Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				curObj->unPress(curObj);
			}
		}
		else
		{
			if (!Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				curObj->unPress(curObj);
			}
		}
	}
}

void GameScene::UpdateButtonEvents()
{
	UpdateButtonOnHover();
	UpdateButtonOnClick();
	UpdateButtonOnPress();
}

// ----------------- GameScene State ----------------- 
void GameScene::GameSceneDraw()
{
	// Render GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (objectsList[idx]->parent != nullptr || !objectsList[idx]->IsActive())
		{
			continue;
		}

		objectsList[idx]->Draw(camera);
	}
	// Render UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (uiObjectsList[idx]->parent != nullptr || !uiObjectsList[idx]->IsActive())
		{
			continue;
		}

		uiObjectsList[idx]->Draw(camera);
	}
}
void GameScene::GameSceneUnload()
{
	// Unload GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		objectsList[idx]->UnloadMesh();
	}
	// Unload UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		uiObjectsList[idx]->UnloadMesh();
	}
	std::cout << "Game Scene(Default) : UnLoad Mesh Completed\n";
}
void GameScene::GameSceneFree()
{
	// Free GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		delete objectsList[idx];
	}
	// Free UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		delete uiObjectsList[idx];
	}
	std::cout << "Game Scene(Default) : Free Memory Completed\n";
}