#include "CasterController.h"
#include "Game/GameData/CasterData/EnemyData.h"

class EnemyController : public CasterController
{
private:
    EnemyMoveSet m_MoveSet;
public:
    EnemyController(EnemyData caster, EnemyMoveSet moveSet) : CasterController(caster), m_MoveSet(moveSet)
    {
        std::cout << "DEBUG ENEMY ELEMENT: " << (int)caster.Element() << "\n";

        this->m_CasterObject->SetCaster(caster.EnemyType(), caster.Element(),CasterPosition::CasterB);
    }

    void CastEnemySpell();
};