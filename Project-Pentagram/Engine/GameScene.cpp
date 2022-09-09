#include "GameScene.h"

// ------------------------ Creating Object ------------------------ 
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

ParticleSystem* GameScene::CreateParticle(ParticleProps& particleProps)
{
	ParticleSystem* particle = new ParticleSystem("Particle_" + std::to_string(objectsList.size()));
	particle->baseParticle = particleProps;
	objectsList.push_back(particle);
	return particle;
}

ParticleSystem* GameScene::CreateParticle(const std::string& objName, ParticleProps& particleProps)
{
	ParticleSystem* particle = new ParticleSystem(objName);
	particle->baseParticle = particleProps;
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

// ------------------------ Button Events ------------------------ 

void GameScene::UpdateButtonOnClick()
{
	if (!Input::IsKeyEndPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		return;
	}
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	for (int idx = buttonObjectsList.size() - 1; idx >= 0; idx--)
	{
		Button* curObj = buttonObjectsList[idx];

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->isActive())
		{
			continue;
		}
		float left = curObj->position.x - (curObj->scale.x / 2.0f);
		float right = curObj->position.x + (curObj->scale.x / 2.0f);
		float top = curObj->position.y + (curObj->scale.y / 2.0f);
		float bottom = curObj->position.y - (curObj->scale.y / 2.0f);

		if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			curObj->onClick(curObj);
		}
	}
}
void GameScene::UpdateButtonOnHover()
{
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetHeight();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	for (int idx = buttonObjectsList.size() - 1; idx >= 0; idx--)
	{
		Button* curObj = buttonObjectsList[idx];

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->isActive())
		{
			continue;
		}
		float left = curObj->position.x - (curObj->scale.x / 2.0f);
		float right = curObj->position.x + (curObj->scale.x / 2.0f);
		float top = curObj->position.y + (curObj->scale.y / 2.0f);
		float bottom = curObj->position.y - (curObj->scale.y / 2.0f);

		if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			curObj->onHover(curObj);
		}
		else
		{
			curObj->unHover(curObj);
		}
	}
}
void GameScene::UpdateButtonEvents()
{
	UpdateButtonOnHover();
	UpdateButtonOnClick();
}

// ------------------------ GameScene State ------------------------ 
void GameScene::GameSceneDraw()
{
	// Render GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (objectsList[idx]->parent != nullptr || !objectsList[idx]->isActive())
		{
			continue;
		}

		objectsList[idx]->Draw(camera);
	}
	// Render UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (uiObjectsList[idx]->parent != nullptr || !uiObjectsList[idx]->isActive())
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