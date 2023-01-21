#pragma once

#include "Engine/GameObjectTag.h"
#include "Engine/GameObject.h"
#include "Engine/ParticleSystem.h"
#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"
#include "Engine/Button.h"
#include "Engine/Slider.h"

class IGameObjectManager
{
	protected:
		virtual void AddGameObjectToList(GameObject* object) = 0;
		virtual void AddUIObjectToList(UIObject* object) = 0;
		virtual void AddButtonToList(Button* object) = 0;

	public:
		template <typename T>
		T* CreateObject(T* object)
		{
			if (GameObject* gameObj = dynamic_cast<GameObject*>(object))
			{
				std::vector<GameObject*> childList = gameObj->GetChildList();
				for (GameObject* child : childList)
				{
					CreateObject(child);
				}
			}

			if (Button* button = dynamic_cast<Button*>(object))
			{
				AddButtonToList(button);
			}
			else if (UIObject* ui = dynamic_cast<UIObject*>(object))
			{
				AddUIObjectToList(ui);
			}
			else if (GameObject* gameObj = dynamic_cast<GameObject*>(object))
			{
				AddGameObjectToList(gameObj);
			}
			return object;
		}

		virtual GameObject* CreateGameObject(const std::string& objName = "", const int& animRow = 1, const std::vector<int>& animCol = { 1 }) = 0;
		virtual ParticleSystem* CreateParticle(ParticleProperty& particleProperty) = 0;
		virtual ParticleSystem* CreateParticle(const std::string& objName, ParticleProperty& particleProperty) = 0;
		virtual UIObject* CreateUIObject(const std::string& objName = "") = 0;
		virtual TextObject* CreateTextObject(const std::string& objName = "") = 0;
		virtual Button* CreateButton(const std::string& objName = "") = 0;
		virtual Slider* CreateSlider(const std::string& objName = "") = 0;
	
		// ----------------- Modify Object -----------------
		virtual void DeleteObjectByName(const std::string& objName) = 0;
		virtual void DeleteObjectByPointer(GameObject* objPtr) = 0;
		virtual GameObject* FindObject(const std::string& objName) = 0;
};