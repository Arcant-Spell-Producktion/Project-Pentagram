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
	obj->SetTexture(path.c_str());
	obj->scale.x = 500.0f;
	obj->scale.y = 500.0f;
	obj->position.x = 500.0f;

	// Init UI
	UIObject* ui = CreateUIObject();
	ui->scale.x = 1600.0f;
	ui->scale.y = 900.0f;
	ui->color = glm::vec4(0.0f, 0.0f, 0.0f, 0.5f);

	UIObject* ui2 = CreateUIObject();
	ui2->scale.x = 500.0f;
	ui2->scale.y = 500.0f;
	ui2->color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	std::cout << "Menu Scene : Initialize Completed\n";
}

void MenuScene::GameSceneUpdate(double dt)
{
	double time = glfwGetTime();

	camera.Input(dt);
	if (uiObjectsList[0]->onClick())
	{
		uiObjectsList[0]->color = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
	}
	else
	{
		uiObjectsList[0]->color = glm::vec4(0.0f, 0.0f, 0.0f, 0.5f);
	}

	if (uiObjectsList[1]->onClick())
	{
		uiObjectsList[1]->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		uiObjectsList[1]->color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
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