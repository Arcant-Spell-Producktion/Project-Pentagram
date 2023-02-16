#include "CursorManager.h"

CursorManager::CursorManager()
{
	cursorObject = new UIObject("CursorObject");
	cursorObject->scale = { 50.0f, 50.0f, 1.0f };
	cursorObject->SetTexture("Sprites/Cursor.png");

	InitParticle(trailParticle, "TrailParticle");
	InitParticle(onClickParticle, "OnClickParticle");
	onClickParticle->baseParticle.velocityVariation = { 250.0f, 250.0f };
	onClickParticle->baseParticle.lifeTime = 0.3f;
	onClickParticle->SetSpawnTime(0.005f);
}

void CursorManager::Update(Camera& camera, float dt)
{
	UpdateCursorPosition();
	UpdateTrailParticle(dt);
	UpdateOnClickParticle(dt);

	trailParticle->Draw(camera);
	onClickParticle->Draw(camera);
	cursorObject->Draw(camera);
}

void CursorManager::Free()
{
	delete cursorObject;
	delete trailParticle;
	delete onClickParticle;
	Singleton::Free();
}

// --------------------- Private Function ---------------------
void CursorManager::InitParticle(ParticleSystem*& particle, std::string objName)
{
	particle = new ParticleSystem(objName);
	particle->baseParticle.sizeBegin = 5.0f;
	particle->baseParticle.sizeEnd = 25.0f;
	particle->baseParticle.lifeTime = 0.75f;
	particle->SetSpawnTime(0.01f);
	particle->SetTexture("Sprites/CursorParticle.png");
}
void CursorManager::UpdateCursorPosition()
{
	glm::dvec2 curPos;
	glm::ivec2 windowPos;
	glfwGetCursorPos(windowRef->GetWindowPointer(), &curPos.x, &curPos.y);
	glfwGetWindowPos(windowRef->GetWindowPointer(), &windowPos.x, &windowPos.y);

	if (curPos.x >= 0 && curPos.x <= windowRef->GetWindowWidth() &&
		curPos.y >= 0 && curPos.y <= windowRef->GetWindowHeight() )
	{
		cursorObject->SetActive(true);
	}
	else
	{
		cursorObject->SetActive(false);
		return;
	}

	glm::vec2 windowSize = { windowRef->GetWindowWidth(), windowRef->GetWindowHeight() };
	glm::vec2 viewportSize = { windowRef->GetViewportWidth(), windowRef->GetViewportHeight() };

	MapCursorPosition(curPos);
	cursorObject->position.x += cursorObject->scale.x / 2.0f;
	cursorObject->position.y -= cursorObject->scale.y / 2.0f;
}
void CursorManager::UpdateTrailParticle(float dt)
{
	if (Input::deltaMouseX != 0.0f || Input::deltaMouseY != 0.0f)
	{
		trailParticle->StartGenerate();
		//particle->baseParticle.velocity = { -Input::deltaMouseX, -Input::deltaMouseY };
		trailParticle->baseParticle.positionVariation = { 0.0f, 2.0f };
		trailParticle->baseParticle.position = { cursorObject->position.x - cursorObject->scale.x / 2.0f,
										cursorObject->position.y + cursorObject->scale.y / 2.0f };
	}
	else
	{
		trailParticle->StopGenerate();
	}
	trailParticle->OnUpdate(dt);
}
void CursorManager::UpdateOnClickParticle(float dt)
{
	if (Input::IsKeyBeginPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		isOnClick = true;

		onClickParticle->baseParticle.position = { cursorObject->position.x - cursorObject->scale.x / 2.0f,
										cursorObject->position.y + cursorObject->scale.y / 2.0f };
		onClickParticle->StartGenerate();
	}

	if (isOnClick)
	{
		onClickCurrentTime += dt;
		if (onClickCurrentTime >= onClickDelayTime)
		{
			onClickParticle->StopGenerate();
			isOnClick = false;
			onClickCurrentTime = 0.0f;
		}
	}
	else
	{
		onClickParticle->StopGenerate();
	}
	onClickParticle->OnUpdate(dt);
}
float CursorManager::MapValue(float value, float orgMin, float orgMax, float newMin, float newMax)
{
	float percentage = (value - orgMin) / (orgMax - orgMin);

	return newMin + percentage * (newMax - newMin);
}
void CursorManager::MapCursorPosition(const glm::vec2& cursorPos)
{
	cursorObject->position.x = MapValue(cursorPos.x, 0, windowRef->GetWindowWidth(), -1920.0f / 2.0f, 1920.0f / 2.0f);
	cursorObject->position.y = MapValue(windowRef->GetWindowHeight() - cursorPos.y, 0, windowRef->GetWindowHeight(), -1080.0f / 2.0f, 1080.0f / 2.0f);
}