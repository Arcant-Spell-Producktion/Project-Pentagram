#include "CasterController.h"
#include "Game/GameData/CasterData/EnemyData.h"

class EnemyController : public CasterController
{
public:
    EnemyController(EnemyData caster) : CasterController(caster)
    {
        std::cout << "DEBUG ENEMY ELEMENT: " << (int)caster.Element() << "\n";

        this->m_CasterObject->SetCaster(caster.EnemyType(), caster.Element(),CasterPosition::CasterB);
    }
};