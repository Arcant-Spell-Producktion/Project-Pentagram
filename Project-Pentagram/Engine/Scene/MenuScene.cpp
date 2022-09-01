#include "Engine/Scene/MenuScene.h"

void MenuScene::GameSceneLoad()
{
	std::cout << "Menu Scene : Load Completed\n";
}

GameObject* cur;
void MenuScene::GameSceneInit()
{
	std::string path = "Sprites/Fire_Mage.png";

	ParticleProps particleProp;
	particleProp.colorBegin = { 1.0f, 0.0f, 0.0f, 1.0f };
	particleProp.colorEnd = { 1.0f, 0.5f, 0.0f, 0.0f };
	particleProp.sizeBegin = particleProp.sizeEnd = 10.0f;
	particleProp.velocityVariation = { 600.0f, 600.0f };
	particleProp.velocity = { 0.0f, 300.0f };
	ParticleSystem* particle = CreateParticle(particleProp);

	GameObject* obj = CreateGameObject("SmileFace", 2, { 5,8 });
	obj->scale = { 320.0f, 320.0f, 1.0f };
	obj->SetTexture(path);
	obj->MakeChild(particle);
	cur = obj;

	GameObject* obj2 = CreateGameObject("Floor");
	obj2->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	obj2->scale = { 1600.0f, 500.0f, 1.0f };
	obj2->position.y = -400.0f;


	GameObject* obj3 = CreateGameObject("SmileFace", 1, {5});
	obj3->scale = { 320.0f, 320.0f, 1.0f };
	obj3->SetTexture("Sprites/character_minion_idle.png");
	obj3->position.x += 500.0f;

	// GameObject* obj2 = CreateGameObject("SmileFace");
	// obj2->scale = { 10.0f, 10.0f, 1.0f };
	// obj2->SetTexture("Sprites/awesomeface.png");

	TextObject* textObj = CreateTextObject("INFO_Text");
	textObj->position = { -800.0f, 400.0f, 0.0f };
	textObj->color = AC_RED;
	textObj->outlineColor = AC_BLUE;
	textObj->textAlignment = TextAlignment::LEFT;
	textObj->SetFonts("Fonts/BAUHS93.ttf");

	TextObject* textObj2 = CreateTextObject("Test_Text");
	textObj2->position = { -600.0f, -250.0f, 0.0f };
	textObj2->color = AC_RED;
	textObj2->textAlignment = TextAlignment::LEFT;
	textObj2->text = "Hello! My name is Helia. I am Fire Mage?\nWho are you? Are you Blue Kiki?\nNah Forget about it";
	textObj2->SetSlowRender(0.050f);

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
	button->textObject.textAlignment = TextAlignment::MID;
	button->textObject.position = { 0.0f, 0.0f, 0.0f };
	button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };


	Button* button2 = CreateButton("Exit_Button");
	button2->scale = { 300.0f, 100.0f, 1.0f };
	button2->position = { 0.0f, -150.0f, 0.0f };
	button2->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	button2->textObject.text = "Exit";
	button2->textObject.textAlignment = TextAlignment::MID;
	button2->textObject.position = { 0.0f, 0.0f, 0.0f };
	button2->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };

	subUI->MakeChild(button);
	subUI->MakeChild(button2);
	ui->SetActive(false);
	std::cout << "Menu Scene : Initialize Completed\n";
}

float t = 0.0f;
void MenuScene::GameSceneUpdate(float dt)
{
	double time = glfwGetTime();
	if (t >= 1.0f)
	{
		t = 0.0f;
	}
	t += dt;

	if (Input::IsKeyBeginPressed(GLFW_KEY_R))
	{
		SceneManager::LoadScene(GameState::GS_RESTART);
		// If not return will cause memory problem
		return;
	}
	if (Input::IsKeyPressed(GLFW_KEY_D) || Input::IsKeyPressed(GLFW_KEY_A))
	{
		cur->SetAnimationState(2);
	}
	else
	{
		cur->SetAnimationState(1);
	}

	if (Input::IsKeyPressed(GLFW_KEY_D))
	{
		cur->scale.x = abs(cur->scale.x);
		cur->position.x += 100.0f * dt;
	}
	else if (Input::IsKeyPressed(GLFW_KEY_A))
	{
		cur->scale.x = -abs(cur->scale.x);
		cur->position.x -= 100.0f * dt;
	}


	// Update GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		GameObject*& curObj = objectsList[idx];

		curObj->OnUpdate(dt);
		if (curObj->isAnimation())
		{
			curObj->UpdateAnimation(dt);
		}
		if (curObj->GetTag() == GameObjectTag::PARTICLE && Input::IsKeyBeginPressed(GLFW_KEY_3))
		{
			curObj->SetActive(curObj->isActive() ? false : true);
		}
	}

	// Update UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		UIObject*& curObj = uiObjectsList[idx];

		if (curObj->name == "INFO_Text" && t >= 1.0f)
		{
			dynamic_cast<TextObject*>(curObj)->text = "FPS : " + std::to_string(int(1.0f / dt)) + "\n" +
				"GameObject : " + std::to_string(objectsList.size()) + "\n" +
				"UIObject : " + std::to_string(uiObjectsList.size());
		}
		else if (curObj->name == "BigUI_1")
		{
			if (Input::IsKeyBeginPressed(GLFW_KEY_ESCAPE))
			{
				curObj->SetActive(curObj->isActive() ? false : true);
			}
		}

		if (!curObj->isActive()) { continue; }

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
		curObj->OnUpdate(dt);
	}
}

void MenuScene::GameSceneDraw()
{
	ShaderCollector* shaderCollector = EngineDataCollector::GetInstance()->GetShaderCollector();
	// Render GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (objectsList[idx]->parent != nullptr || !objectsList[idx]->isActive())
		{
			continue;
		}

		objectsList[idx]->Draw(shaderCollector->GameObjectShader, camera);
	}
	// Render UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		// If current Object was child -> no need to draw
		if (uiObjectsList[idx]->parent != nullptr || !uiObjectsList[idx]->isActive())
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