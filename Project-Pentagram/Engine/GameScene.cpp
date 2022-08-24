#include "GameScene.h"

GameObject* GameScene::CreateGameObject()
{
	GameObject* obj = new GameObject();
	objectsList.push_back(obj);
	return obj;
}

ParticleSystem* GameScene::CreateParticle(ParticleProps& particleProps)
{
	ParticleSystem* particle = new ParticleSystem();
	particle->baseParticle = particleProps;
	particleList.push_back(particle);
	return particle;
}

UIObject* GameScene::CreateUIObject()
{
	UIObject* ui = new UIObject();
	ui->uiList = &uiObjectsList;
	uiObjectsList.push_back(ui);
	return ui;
}