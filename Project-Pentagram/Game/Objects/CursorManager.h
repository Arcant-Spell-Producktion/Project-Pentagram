#pragma once

#include "Engine/UIObject.h"
#include "Engine/GameStateController.h"

class CursorManager : public Singleton<CursorManager>
{
	private:
		UIObject* cursorObject;
		ParticleSystem* trailParticle;
		ParticleSystem* onClickParticle;
		float onClickDelayTime = 0.2f;
		float onClickCurrentTime = 0.0f;
		bool isOnClick = false;

		Window* windowRef = ArcantEngine::GetInstance()->GetWindow();

		void InitParticle(ParticleSystem*& particle, std::string objName);
		void UpdateCursorPosition();
		void UpdateTrailParticle(float dt);
		void UpdateOnClickParticle(float dt);
		float MapValue(float value, float orgMin, float orgMax, float newMin, float newMax);
		void MapCursorPosition(const glm::vec2& cursorPos);
	public:
		CursorManager();

		void Update(Camera& camera, float dt);

		void Free();
};