#include "PlayerController.h"

#include "Game/BattleScene/BattleManager.h"

void PlayerController::CasterDied()
{
    m_IsAlive = false;
    BattleManager::GetInstance().EndBattle();
}

PlayerController::PlayerController(CasterData caster) : CasterController(caster)
{
	auto element = m_CasterManager.Data().Element();
	auto position = m_CasterManager.Data().Position();
	this->m_CasterObject->SetCaster(CasterType::Player, element, position);
}

