#include "GameScene.h"

GameObject* GameScene::CreateGameObject(const std::string& objName)
{
	GameObject* obj;
	if (objName == "")
	{
		obj = new GameObject("GameObject_" + std::to_string(objectsList.size()));
	}
	else
	{
		obj = new GameObject(objName);
	}

	objectsList.push_back(obj);
	return obj;
}

ParticleSystem* GameScene::CreateParticle(ParticleProps& particleProps)
{
	ParticleSystem* particle = new ParticleSystem("Particle_" + std::to_string(objectsList.size()));
	particle->baseParticle = particleProps;
	objectsList.push_back(particle);
	return particle;
}

ParticleSystem* GameScene::CreateParticle(const std::string & objName, ParticleProps & particleProps)
{
	ParticleSystem* particle = new ParticleSystem(objName);
	particle->baseParticle = particleProps;
	objectsList.push_back(particle);
	return particle;
}

UIObject* GameScene::CreateUIObject(const std::string& objName)
{
	UIObject* ui;
	if (objName == "")
	{
		ui = new UIObject("UI_" + std::to_string(uiObjectsList.size()));
	}
	else
	{
		ui = new UIObject(objName);
	}

	uiObjectsList.push_back(ui);
	return ui;
}

TextObject* GameScene::CreateTextObject(const std::string& objName)
{
	TextObject* textObj;
	if (objName == "")
	{
		textObj = new TextObject("TextObject_" + std::to_string(uiObjectsList.size()));
	}
	else
	{
		textObj = new TextObject(objName);
	}
	uiObjectsList.push_back(textObj);
	return textObj;
	
}

Button* GameScene::CreateButton(const std::string& objName)
{
	Button* button;
	if (objName == "")
	{
		button = new Button("Button_" + std::to_string(uiObjectsList.size()));
	}
	else
	{
		button = new Button(objName);
	}
	button->uiList = &uiObjectsList;
	uiObjectsList.push_back(button);
	return button;
}