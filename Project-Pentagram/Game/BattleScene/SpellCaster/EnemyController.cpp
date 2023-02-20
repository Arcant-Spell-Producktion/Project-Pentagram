#include "EnemyController.h"

void EnemyController::CastEnemySpell()
{
    int currentMana = m_CasterManager.GetMana();
    PentagramData_T currentPentagram = m_MoveSet.GetMove(currentMana - 1);

    m_CasterManager.SetPentagramData(currentPentagram);

    while(!m_CasterManager.CanCastSpell() && currentMana - 1 > 0)
    {
        currentMana--;
        currentPentagram = m_MoveSet.GetMove(currentMana - 1);
        m_CasterManager.SetPentagramData(currentPentagram);
    }
    if (currentMana > 0)
    {
        CastSpell();
    }
}
