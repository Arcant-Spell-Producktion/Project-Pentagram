#include "GameScene.h"

GameScene::~GameScene()
{

}

void GameScene::AddGameObjectToList(GameObject* object)
{
	objectsList.push_back(object);
}
void GameScene::AddUIObjectToList(UIObject* object)
{
	uiObjectsList.push_back(object);
}
void GameScene::AddButtonToList(Button* object)
{
	uiObjectsList.push_back(object);
	buttonObjectsList.push_back(object);
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

	uiObjectsList.push_back(slider->GetSliderButton());
	buttonObjectsList.push_back(slider->GetSliderButton());

	return slider;
}

// ----------------- Modify Object -----------------
void GameScene::DeleteObjectByName(const std::string& objName)
{
	// Find Object in objectsList
	for (auto obj = objectsList.begin(); obj != objectsList.end(); obj++)
	{
		if ((*obj)->name == objName)
		{
			objectsToDeleteList.push_back(*obj);
		}
	}

	// Find Object in uiObjectsList
	for (auto uiObj = uiObjectsList.begin(); uiObj != uiObjectsList.end(); uiObj++)
	{
		if ((*uiObj)->name == objName)
		{
			objectsToDeleteList.push_back(*uiObj);
		}
	}
}
void GameScene::DeleteObjectByPointer(GameObject* objPtr)
{
	objectsToDeleteList.push_back(objPtr);
}
GameObject* GameScene::FindObject(const std::string& objName)
{
	// Find in objectsList
	for (GameObject* currentObj : objectsList)
	{
		if (currentObj->name == objName)
		{
			return currentObj;
		}
	}

	// Find in uiObjectsList
	for (UIObject* currentUIObj : uiObjectsList)
	{
		if (currentUIObj->name == objName)
		{
			return currentUIObj;
		}
	}

	return nullptr;
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
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWindowWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetWindowHeight();

	glm::vec2 viewportScale = ArcantEngine::GetInstance()->GetWindow()->GetViewportDiffRatio();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	for (int idx = uiObjectsList.size() - 1; idx >= 0; idx--)
	{
		UIObject* curObj = uiObjectsList[idx];
		Button* buttonCurObj = dynamic_cast<Button*>(curObj);
		glm::vec3 finalPos = curObj->position;
		if (buttonCurObj)
		{
			finalPos = FindButtonParentPosition(buttonCurObj);
		}

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->IsActive())
		{
			continue;
		}
		float left = (finalPos.x - (curObj->scale.x / 2.0f)) * viewportScale.x;
		float right = (finalPos.x + (curObj->scale.x / 2.0f)) * viewportScale.x;
		float top = (finalPos.y + (curObj->scale.y / 2.0f)) * viewportScale.y;
		float bottom = (finalPos.y - (curObj->scale.y / 2.0f)) * viewportScale.y;

		if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			if (!buttonCurObj) { return; }

			buttonCurObj->onClick.Invoke(buttonCurObj);
			return;
		}
	}
}
void GameScene::UpdateButtonOnHover()
{
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWindowWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetWindowHeight();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	bool isHover = false;

	glm::vec2 viewportScale = ArcantEngine::GetInstance()->GetWindow()->GetViewportDiffRatio();

	for (int idx = uiObjectsList.size() - 1; idx >= 0; idx--)
	{
		UIObject* curObj = uiObjectsList[idx];
		Button* buttonCurObj = dynamic_cast<Button*>(curObj);
		glm::vec3 finalPos = curObj->position;
		if (buttonCurObj)
		{
			finalPos = FindButtonParentPosition(buttonCurObj);
		}

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->IsActive())
		{
			continue;
		}
		float left = (finalPos.x - (curObj->scale.x / 2.0f)) * viewportScale.x;
		float right = (finalPos.x + (curObj->scale.x / 2.0f)) * viewportScale.x;
		float top = (finalPos.y + (curObj->scale.y / 2.0f)) * viewportScale.y;
		float bottom = (finalPos.y - (curObj->scale.y / 2.0f)) * viewportScale.y;

		if (!isHover && (curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			if (!buttonCurObj) {  isHover = true; continue; }

			buttonCurObj->onHover(buttonCurObj);
			isHover = true;
		}
		else
		{
			if (!buttonCurObj) { continue; }

			buttonCurObj->unHover(buttonCurObj);
		}
	}
}
void GameScene::UpdateButtonOnPress()
{
	int screen_width = ArcantEngine::GetInstance()->GetWindow()->GetWindowWidth();
	int screen_height = ArcantEngine::GetInstance()->GetWindow()->GetWindowHeight();

	float curX = (Input::mouseX - screen_width / 2.0f);
	float curY = (screen_height / 2.0f - Input::mouseY);

	glm::vec2 viewportScale = ArcantEngine::GetInstance()->GetWindow()->GetViewportDiffRatio();

	for (int idx = uiObjectsList.size() - 1; idx >= 0; idx--)
	{
		UIObject* curObj = uiObjectsList[idx];
		Button* buttonCurObj = dynamic_cast<Button*>(curObj);
		glm::vec3 finalPos = curObj->position;
		if (buttonCurObj)
		{
			finalPos = FindButtonParentPosition(buttonCurObj);
		}

		// If current Object is inactive (Not Render) => No need to check collision
		if (curObj == nullptr || !curObj->IsActive())
		{
			continue;
		}
		float left = (finalPos.x - (curObj->scale.x / 2.0f)) * viewportScale.x;
		float right = (finalPos.x + (curObj->scale.x / 2.0f)) * viewportScale.x;
		float top = (finalPos.y + (curObj->scale.y / 2.0f)) * viewportScale.y;
		float bottom = (finalPos.y - (curObj->scale.y / 2.0f)) * viewportScale.y;

		if ((curX <= right && curX >= left) && (curY <= top && curY >= bottom))
		{
			if (!buttonCurObj) { continue; }

			if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				buttonCurObj->onPress(buttonCurObj);
				return;
			}
			else if(!Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				buttonCurObj->unPress(buttonCurObj);
			}
		}
		else
		{
			if (!buttonCurObj) { continue; }

			if (!Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				buttonCurObj->unPress(buttonCurObj);
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
void GameScene::GameSceneUpdate(float dt)
{
	UpdateScaleDeltaTime(dt);
	UpdateDeleteObject();
	UpdateButtonEvents();
	camera.OnUpdate(dt);
}
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

void GameScene::UpdateScaleDeltaTime(float deltaTime)
{
	this->scaledDeltaTime = deltaTime * timeScale;
}
void GameScene::UpdateDeleteObject()
{
	if (!objectsToDeleteList.empty())
	{
		for (int idx = 0; idx < objectsToDeleteList.size(); idx++)
		{
			GameObject* deleteObject = objectsToDeleteList[idx];
			// ----------------- Hierarchy Session ----------------- 
			// If deleteObject have parent
			if (deleteObject->parent != nullptr)
			{
				deleteObject->parent->RemoveChild(deleteObject);
			}
			// If deleteObject have child
			if (deleteObject->GetChildSize() != 0)
			{
				std::vector<GameObject*> childList = deleteObject->GetChildList();
				for (GameObject* childObj : childList)
				{
					// Set child->parent to nullptr = current parent will be deleted
					childObj->parent = nullptr;
					objectsToDeleteList.push_back(childObj);
				}
			}

			// ----------------- Delete Session -----------------
			if (dynamic_cast<Button*>(deleteObject) != nullptr)
			{
				buttonObjectsList.erase(std::remove(buttonObjectsList.begin(), buttonObjectsList.end(), deleteObject), buttonObjectsList.end());
				uiObjectsList.erase(std::remove(uiObjectsList.begin(), uiObjectsList.end(), deleteObject), uiObjectsList.end());
			}
			else if (dynamic_cast<UIObject*>(deleteObject) != nullptr)
			{
				uiObjectsList.erase(std::remove(uiObjectsList.begin(), uiObjectsList.end(), deleteObject), uiObjectsList.end());
			}
			else if (dynamic_cast<GameObject*>(deleteObject) != nullptr)
			{
				objectsList.erase(std::remove(objectsList.begin(), objectsList.end(), deleteObject), objectsList.end());
			}

			deleteObject->UnloadMesh();
			delete deleteObject;
		}

		objectsToDeleteList.clear();
	}
}


// ----------------- Getter Implement -----------------
AudioController* GameScene::GetAudioController() const
{
	return this->audioController;
}
Camera* GameScene::GetCamera()
{
	return &(this->camera);
}