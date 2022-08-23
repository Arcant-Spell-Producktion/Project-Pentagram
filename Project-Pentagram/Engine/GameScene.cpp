#include "GameScene.h"

GameObject* GameScene::CreateGameObject()
{
	GameObject* obj = new GameObject();
	objectsList.push_back(obj);
	return obj;
}

UIObject* GameScene::CreateUIObject()
{
	UIObject* ui = new UIObject();
	ui->uiList = &uiObjectsList;
	uiObjectsList.push_back(ui);
	return ui;
}