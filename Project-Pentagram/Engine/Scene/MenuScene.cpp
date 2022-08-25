#include "../Scene/MenuScene.h"

void MenuScene::GameSceneLoad()
{
	std::cout << "Menu Scene : Load Completed\n";
}

void MenuScene::GameSceneInit()
{
	std::string path = "Sprites/awesomeface.png";

	GameObject* emptyObj = CreateGameObject("Empty_Object");

	GameObject* obj = CreateGameObject("SmileFace");
	obj->position = { 500.0f, 0.0f, 0.0f };
	obj->scale = { 200.0f, 200.0f, 1.0f};
	obj->SetTexture(path);
	emptyObj->MakeChild(obj);

	UIObject* ui = CreateUIObject("BigUI_1");
	ui->scale = { 1600.0f, 900.0f, 1.0f };
	ui->color = { 0.0f, 0.0f, 0.0f, 0.5f };

	UIObject* subUI = CreateUIObject();
	subUI->scale = { 800.0f, 700.0f, 1.0f };
	subUI->color = { 0.8f, 0.8f, 0.8f, 1.0f };
	ui->MakeChild(subUI);

	Button* button = CreateButton("Options_Button");
	button->scale = { 300.0f, 100.0f, 1.0f };
	button->position = { 0.0f, 150.0f, 0.0f };
	button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	button->textObject.text = "Options";
	button->textObject.position = { 0.0f, 0.0f, 0.0f };
	button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };


	Button* button2 = CreateButton("Exit_Button");
	button2->scale = { 300.0f, 100.0f, 1.0f };
	button2->position = { 0.0f, -150.0f, 0.0f };
	button2->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	button2->textObject.text = "Exit";
	button2->textObject.position = { 0.0f, 0.0f, 0.0f };
	button2->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };

	subUI->MakeChild(button);
	subUI->MakeChild(button2);
	ui->active = false;

	std::cout << "Menu Scene : Initialize Completed\n";
}

void MenuScene::GameSceneUpdate(double dt)
{
	double time = glfwGetTime();

	camera.Input((float)dt);

	// Update GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		GameObject*& curObj = objectsList[idx];
		if (curObj->name == "Empty_Object")
		{
			curObj->rotation += dt * 10.0f;
		}

		curObj->OnUpdate((float)dt);
	}

	// Update UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		UIObject* &curObj = uiObjectsList[idx];
		if (curObj->name == "BigUI_1")
		{
			if (Input::IsKeyBeginPressed(GLFW_KEY_1))
			{
				curObj->active = (curObj->active ? false : true);
			}
		}
		else if (curObj->name == "Options_Button")
		{
			Button* curButton = dynamic_cast<Button*>(curObj);
			if (curButton->onHover())
			{
				curButton->color = { 0.9f, 0.9f, 0.9f, 1.0f };
			}
			else
			{
				curButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
			}
		}
		else if (curObj->name == "Exit_Button")
		{
			Button* curButton = dynamic_cast<Button*>(curObj);
			if (curButton->onHover())
			{
				curButton->color = { 0.9f, 0.9f, 0.9f, 1.0f };
			}
			else
			{
				curButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
			}

			if (curButton->onClick())
			{
				GameStateController::GetInstance()->currentState = GameState::GS_QUIT;
			}
		}
	}
}

void MenuScene::GameSceneDraw()
{
	ShaderCollector* shaderCollector = ShaderCollector::GetInstance();
	// Render GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (objectsList[idx]->parent != nullptr)
		{
			continue;
		}

		objectsList[idx]->Draw(shaderCollector->GameObjectShader, camera);
	}
	// Render UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (uiObjectsList[idx]->parent != nullptr)
		{
			continue;
		}

		uiObjectsList[idx]->Draw(shaderCollector->GameObjectShader, camera);
	}
}

void MenuScene::GameSceneUnload()
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
	std::cout << "Menu Scene : UnLoad Mesh Completed\n";
}

void MenuScene::GameSceneFree()
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
	std::cout << "Menu Scene : Free Memory Completed\n";
}