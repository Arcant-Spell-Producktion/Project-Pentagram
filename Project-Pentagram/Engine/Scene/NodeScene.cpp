#include "Engine/Scene/NodeScene.h"

void NodeScene::GameSceneLoad()
{
	std::cout << "Node Scene : Load Completed\n";
}

void NodeScene::GameSceneInit()
{
	std::cout << "Node Scene : Initialize Completed\n";
}

void NodeScene::GameSceneUpdate(float dt)
{

}

void NodeScene::GameSceneFree()
{
	std::cout << "Node Scene : Free Memory\n";
}