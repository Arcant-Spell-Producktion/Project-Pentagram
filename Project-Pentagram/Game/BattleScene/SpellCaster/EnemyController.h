#include "CasterController.h"
#include "Game/GameData/CasterData/EnemyData.h"

class EnemyController : public CasterController
{
protected:
    CasterMoveSet m_MoveSet;
public:
    EnemyController(EnemyData caster) : CasterController(caster), m_MoveSet(caster.EnemyMoves())
    {
        std::cout << "DEBUG ENEMY ELEMENT: " << (int)caster.Element() << "\n";



        this->m_CasterObject->SetCaster(caster.EnemyType(), caster.Element(),CasterPosition::CasterB);
    }

    void CastEnemySpell();

    void CastEnemySpell(PentagramData_T pentagram);

};