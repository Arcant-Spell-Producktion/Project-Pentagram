#pragma once
#include "EnemyController.h"

class BossController : public EnemyController
{
private:
    void SetElement(Element::Type element)
    {
        m_CasterManager.SetCasterElement(element);
        m_CasterObject->SetCaster(CasterType::BigBoss,element);
    }

public:
    BossController(EnemyData caster) : EnemyController(caster){}
    void ChangeElement()
    {
        Element::Type element = m_CasterManager.Data().Element();
        element = static_cast<Element::Type>((static_cast<int>(element) + 1) % 4);
        SetElement(element);
    };

    void StartRound() override
    {
        ChangeElement();
        CasterController::StartRound();
    };
};