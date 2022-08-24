#include "../Scene/MenuScene.h"

void MenuScene::GameSceneLoad()
{
	std::cout << "Menu Scene : Load Completed\n";
}

void MenuScene::GameSceneInit()
{
	std::string path = "Sprites/awesomeface.png";
	// Init GameObject
	GameObject* obj = CreateGameObject();
	obj->SetTexture(path);
	obj->scale.x = 500.0f;
	obj->scale.y = 500.0f;
	obj->position.x = 500.0f;

	ParticleProps particleProps;
	particleProps.colorBegin = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particleProps.colorEnd = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	particleProps.sizeBegin = 20.0f, particleProps.sizeEnd = 20.0f, particleProps.sizeVariation = 5.0f;
	particleProps.lifeTime = 2.0f;
	particleProps.velocity.y = 200.0f;
	particleProps.velocityVariation = glm::vec2(200.0f, 50.0f);

	ParticleSystem* particle = CreateParticle(particleProps);
	particle->SetTexture(path);
	particle->spawnTime = 0.1f;

	// Init UI
	UIObject* ui = CreateUIObject();
	ui->textUI.text = "FPS : ";
	ui->textUI.position = glm::vec3(-800.0f, 425.0f, 0.0f);
	ui->scale.x = 1600.0f;
	ui->scale.y = 900.0f;
	ui->color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	

	std::cout << "Menu Scene : Initialize Completed\n";
}

float trackTime = 0.0f;
void MenuScene::GameSceneUpdate(double dt)
{
	double time = glfwGetTime();

	camera.Input(dt);
	
	if (Input::IsKeyBeginPressed(GLFW_KEY_1))
	{
		uiObjectsList[0]->active = uiObjectsList[0]->active ? false : true;
	}

	trackTime += dt;
	if (trackTime >= 1.0f)
	{
		uiObjectsList[0]->textUI.text = "FPS : " + std::to_string((int)(1.0f / dt));
		trackTime = 0.0f;
	}

	if (Input::IsKeyBeginPressed(GLFW_KEY_R))
	{
		SceneManager::LoadScene(GameState::GS_MENU_SCENE);
	}

	// Update Particle
	for (GLuint idx = 0; idx < particleList.size(); idx++)
	{
		particleList[idx]->OnUpdate(dt);
	}
}

void MenuScene::GameSceneDraw()
{
	ShaderCollector* shaderCollector = ShaderCollector::GetInstance();
	// Render GameObject
	for (GLuint idx = 0; idx < objectsList.size(); idx++)
	{
		objectsList[idx]->Draw(shaderCollector->GameObjectShader, camera);
	}
	// Render Particle
	for (GLuint idx = 0; idx < particleList.size(); idx++)
	{
		particleList[idx]->Draw(shaderCollector->GameObjectShader, camera);
	}
	// Render UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
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
	// Unload Particle
	for (GLuint idx = 0; idx < particleList.size(); idx++)
	{
		particleList[idx]->UnloadMesh();
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
	// Free Particle
	for (GLuint idx = 0; idx < particleList.size(); idx++)
	{
		delete particleList[idx];
	}
	// Free UI
	for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
	{
		delete uiObjectsList[idx];
	}
	std::cout << "Menu Scene : Free Memory Completed\n";
}