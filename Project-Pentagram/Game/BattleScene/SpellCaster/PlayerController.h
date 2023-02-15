#include "CasterController.h"

class PlayerController : public CasterController
{
public:
    PlayerController(CasterData caster) : CasterController(caster)
    {
        auto element = m_CasterManager.Data().Element();
        auto position = m_CasterManager.Data().Position();
        this->m_CasterObject->SetCaster(CasterType::Player,element,position);
    }
};