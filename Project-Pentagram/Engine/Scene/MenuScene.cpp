#include "../Scene/MenuScene.h"

void MenuScene::GameSceneLoad()
{
	std::cout << "Menu Scene : Load Completed\n";
}

void MenuScene::GameSceneInit()
{
	std::string path = "Sprites/awesomeface.png";
	// Init GameObject
	GameObject* obj = new GameObject();
	obj->SetTexture(path.c_str());
	obj->scale.x = 500.0f;
	obj->scale.y = 500.0f;
	objectsList.push_back(obj);

	// Init UI
	UI* ui = new UI();
	ui->SetTexture(path.c_str());
	ui->scale.x = 500.0f;
	ui->scale.y = 500.0f;
	ui->position.x = -550.0f;
	ui->position.z = 1.0f;
	ui->color = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
	uiList.push_back(ui);

	UI* ui2 = new UI();
	ui2->scale.x = 500.0f;
	ui2->scale.y = 500.0f;
	ui2->position.x = 550.0f;
	ui2->position.z = 1.0f;
	ui2->color = glm::vec4(0.0f, 0.0f, 1.0f, 0.5f);
	uiList.push_back(ui2);

	std::cout << "Menu Scene : Initialize Completed\n";
}

void MenuScene::GameSceneUpdate(double dt)
{
	double time = glfwGetTime();

	camera.Input(dt);
	objectsList[0]->rotation += dt * 25.0f;

		if (uiList[0]->onClick())
		{
			uiList[0]->color = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
		}
		else
		{
			uiList[0]->color = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
		}

		if (uiList[1]->onHover())
		{
			uiList[1]->color = glm::vec4(1.0f, 1.0f, 0.0f, 0.5f);
		}
		else
		{
			uiList[1]->color = glm::vec4(0.0f, 0.0f, 1.0f, 0.5f);
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
	for (GLuint idx = 0; idx < uiList.size(); idx++)
	{
		uiList[idx]->Draw(shaderCollector->GameObjectShader, camera);
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
	for (GLuint idx = 0; idx < uiList.size(); idx++)
	{
		uiList[idx]->UnloadMesh();
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
	for (GLuint idx = 0; idx < uiList.size(); idx++)
	{
		delete uiList[idx];
	}
	std::cout << "Menu Scene : Free Memory Completed\n";
}