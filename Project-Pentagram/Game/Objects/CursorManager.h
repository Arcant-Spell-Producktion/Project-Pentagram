#pragma once

#include "Engine/UIObject.h"
#include "Engine/GameStateController.h"

class CursorManager : public Singleton<CursorManager>
{
	private:
		UIObject* cursorObject;
	public:
		CursorManager()
		{
			cursorObject = new UIObject("CursorObject");
			cursorObject->scale = { 50.0f, 50.0f, 1.0f };
			cursorObject->SetTexture("Sprites/awesomeface.png");
		}

		void Update(Camera& camera, float dt)
		{
			if (GameStateController::GetInstance()->currentState == GameState::GS_LOAD_SCENE)
			{
				cursorObject->rotation += 1.0f;
			}
			else
			{
				cursorObject->rotation = 0.0f;
			}
			Window* window = ArcantEngine::GetInstance()->GetWindow();
			glm::dvec2 curPos;
			glfwGetCursorPos(window->GetWindowPointer(), &curPos.x, &curPos.y);

			glm::vec2 windowSize = { window->GetWindowWidth(), window->GetWindowHeight() };
			cursorObject->position = { curPos.x - windowSize.x / 2.0f, windowSize.y / 2.0f - curPos.y, 0.0f };
			cursorObject->Draw(camera);
		}

		void Free()
		{
			delete cursorObject;
			Singleton::Free();
		}
};