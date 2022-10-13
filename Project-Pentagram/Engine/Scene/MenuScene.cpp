#include "Engine/Scene/MenuScene.h"
#include <Game/Objects/StageObject.h>

float t = 0.0f;
void MenuScene::GameSceneLoad()
{
	std::cout << "Menu Scene : Load Completed\n";
}

GameObject* cur;
Button* curButton;
UIObject* curUI;
UIObject* gObject;
Slider* slider;

void MenuScene::GameSceneInit()
{
	t = 0.0f;

    objectsList.push_back(new StageObject(Element::Water));

	ParticleProperty particleProp;
	particleProp.position = { 0.0f, 600.0f };
	particleProp.colorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
	particleProp.colorEnd = { 1.0f, 1.0f, 1.0f, 1.0f };
	particleProp.sizeBegin = particleProp.sizeEnd = 600.0f;
	particleProp.rotation = -45.0f;
	particleProp.rotationVariation = 0.0f;
	particleProp.velocity = { 700.0f, -1000.0f };
	particleProp.velocityVariation = { 700.0f, 100.0f };
	particleProp.lifeTime = 1.5f;
	ParticleSystem* particle = CreateParticle(particleProp);
	particle->SetTexture("Sprites/Spell/Fire/spell_fire_3.png");
	particle->SetIsAnimationObject(true);
	particle->SetIsFixRotation(true);
	particle->SetSpawnTime(0.25f);

	GameObject* obj = CreateGameObject("FireMage");
	obj->scale = { 320.0f, 320.0f, 1.0f };
	obj->SetTexture("Sprites/Character/Player/character_player_fire.png");
	obj->SetIsAnimationObject(true);
	obj->SetChildRenderBack(particle);
	obj->position = { -500.0f, -150.0f, 0.0f };
	cur = obj;

	GameObject* obj3 = CreateGameObject("WaterKiki");
	obj3->scale = { -320.0f, 320.0f, 1.0f };
	obj3->SetTexture("Sprites/Character/Minion/character_minion_water.png");
	obj3->SetIsAnimationObject(true);
	obj3->position = { 500.0f, -150.0f, 0.0f };

	// GameObject* obj2 = CreateGameObject("SmileFace");
	// obj2->scale = { 10.0f, 10.0f, 1.0f };
	// obj2->SetTexture("Sprites/awesomeface.png");

	TextObject* textObj = CreateTextObject("INFO_Text");
	textObj->position = { -900.0f, 500.0f, 0.0f };
	textObj->color = AC_RED;
	textObj->outlineColor = AC_BLUE;
	textObj->textAlignment = TextAlignment::LEFT;
	textObj->SetFonts("Fonts/BAUHS93.ttf");

	TextObject* textObj2 = CreateTextObject("Test_Text");
	textObj2->position = { -500.0f, -425.0f, 0.0f };
	textObj2->color = AC_WHITE;
	textObj2->textAlignment = TextAlignment::LEFT;
	textObj2->text = R"(Hello! My name is Helia. I am Fire Mage?
						Who are you? Are you Blue Kiki?)";
	textObj2->SetSlowRender(0.075f);

	UIObject* ui = CreateUIObject("BigUI_1");
	ui->scale = { 1920.0f, 1080.0f, 1.0f };
	ui->color = { 0.0f, 0.0f, 0.0f, 0.5f };

	UIObject* subUI = CreateUIObject();
	subUI->scale = { 800.0f, 700.0f, 1.0f };
	subUI->color = { 0.8f, 0.8f, 0.8f, 1.0f };
	subUI->position.y += 100.0f;
	ui->SetChildRenderFront(subUI);
	curUI = subUI;

	Button* button = CreateButton("Options_Button");
	button->scale = { 300.0f, 100.0f, 1.0f };
	button->position = { 0.0f, 150.0f, 0.0f };
	button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	button->SetSlicingBorderMultiplier(0.25f);
	button->textObject.text = "Options";
	button->textObject.textAlignment = TextAlignment::MID;
	button->textObject.position = { 0.0f, 0.0f, 0.0f };
	button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
	button->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
	button->SetTexture("Sprites/Button_Test.png");
	curButton = button;

	Button* button2 = CreateButton("Exit_Button");
	button2->scale = { 300.0f, 100.0f, 1.0f };
	button2->position = { 0.0f, -150.0f, 0.0f };
	button2->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	button2->SetSlicingBorderMultiplier(0.25f);
	button2->textObject.text = "Exit";
	button2->textObject.textAlignment = TextAlignment::MID;
	button2->textObject.position = { 0.0f, 0.0f, 0.0f };
	button2->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
	button2->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
	button2->onClick = [](Button* button) { SceneManager::QuitGame(); };
	button2->SetTexture("Sprites/Button_Test.png");

	UIObject* gradiant = CreateUIObject("Gradient");
	gradiant->SetTexture("Sprites/UI/Game/Caster/ui_game_caster_hp-bar.png");
	gradiant->SetStartGradientTexture("Sprites/GradientMap/gradiant-map_green.png");
	gradiant->SetEndGradientTexture("Sprites/GradientMap/gradiant-map_red.png");
	gradiant->SetIsGradient(true);
	gradiant->scale = { 1280.0f, 320.0f, 1.0f };
	gradiant->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	gradiant->position = { 0.0f, -500.0f, 0.0f};
	gObject = gradiant;

	slider = CreateSlider("Sliding");
	slider->color = AC_YELLOW;

	subUI->SetChildRenderFront(button);
	subUI->SetChildRenderFront(button2);
	subUI->SetChildRenderFront(slider);
	subUI->SetChildRenderFront(gradiant);
	ui->SetActive(false);
	std::cout << "Menu Scene : Initialize Completed\n";

	soundSystem->PlayGroupAudio("Water_Theme_BGM", { "Audio/BGM/Water/bgm_water_1-1.wav", "Audio/BGM/Water/bgm_water_1-3.wav","Audio/BGM/Water/bgm_water_1-4.wav" }, 0.5f);
    soundSystem->Mute("Water_Theme_BGM", "Audio/BGM/Water/bgm_water_1-4.wav");
}

void MenuScene::GameSceneUpdate(float dt)
{
	GameScene::GameSceneUpdate(dt);

	gObject->SetGradientValue(slider->GetValue());

	double time = glfwGetTime();
	if (t >= 1.0f)
	{
		t = 0.0f;
	}
	t += dt;

	if (Input::IsKeyBeginPressed(GLFW_KEY_R))
	{
		SceneManager::RestartScene();
	}
	else if (Input::IsKeyBeginPressed(GLFW_KEY_1))
	{
		if (soundSystem->IsMute("Water_Theme_BGM", "Audio/BGM/Water/bgm_water_1-1.wav"))
		{
			soundSystem->UnMute("Water_Theme_BGM", "Audio/BGM/Water/bgm_water_1-1.wav");
            soundSystem->Mute("Water_Theme_BGM", "Audio/BGM/Water/bgm_water_1-4.wav");
		}
		else
		{
            soundSystem->Mute("Water_Theme_BGM", "Audio/BGM/Water/bgm_water_1-1.wav");
            soundSystem->UnMute("Water_Theme_BGM", "Audio/BGM/Water/bgm_water_1-4.wav");
		}
	}
	else if (Input::IsKeyBeginPressed(GLFW_KEY_9))
	{
		SceneManager::LoadScene(GameState::GS_BATTLE_SCENE);
	}
	else if (Input::IsKeyBeginPressed(GLFW_KEY_Z))
	{
		if (camera.GetZoom() == 1.0f)
		{
			camera.SetZoom(1.25f);
		}
		else
		{
			camera.SetZoom(1.0f);
		}
	}
	else if (Input::IsKeyBeginPressed(GLFW_KEY_Y))
	{
		slider->SetValue(0.75f);
		ArcantEngine::GetInstance()->GetWindow()->SetFullScreen(ArcantEngine::GetInstance()->GetWindow()->IsFullScreen() ? false : true);
	}

	// Update GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		GameObject*& curObj = objectsList[idx];

		curObj->OnUpdate(dt);
		if (curObj->IsAnimationObject())
		{
			curObj->UpdateAnimation(dt);
		}
		if (curObj->GetTag() == GameObjectTag::PARTICLE && Input::IsKeyBeginPressed(GLFW_KEY_4))
		{
			curObj->SetActive(curObj->IsActive() ? false : true);
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
				timeScale = timeScale == 0.0f ? 1.0f : 0.0f;
				curObj->SetActive(curObj->IsActive() ? false : true);
			}
		}

		if (!curObj->IsActive()) { continue; }
		curObj->OnUpdate(dt);
	}
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
	//soundSystem->FreeSound();
	std::cout << "Menu Scene : Free Memory Completed\n";
}