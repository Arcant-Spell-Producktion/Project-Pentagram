#include "../Scene/NodeScene.h"
#include "../SceneManager.h"
#include "../Input.h"

void NodeScene::GameSceneLoad()
{
	std::cout << "Node Scene : Load Completed\n";
}

void NodeScene::GameSceneInit()
{
	std::cout << "Node Scene : Initialize Completed\n";
}

void NodeScene::GameSceneUpdate(double dt)
{

}

void NodeScene::GameSceneDraw()
{

}

void NodeScene::GameSceneUnload()
{
	std::cout << "Node Scene : UnLoad Mesh Completed\n";
}

void NodeScene::GameSceneFree()
{
	std::cout << "Node Scene : Free Memory\n";
}