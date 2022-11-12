#include "CasterController.h"

class PlayerController : public CasterController
{
public:
    PlayerController(CasterData caster) : CasterController(caster)
    {
        auto element = m_SpellCaster.GetCasterData()->GetElement();
        auto position = m_SpellCaster.GetCasterData()->GetPosition();
        this->m_CasterObject->SetCaster(CasterObjectType::Player,element,position);
    }
};