#include "EnemyController.h"

void EnemyController::CastEnemySpell()
{
    int currentMana = m_CasterManager.GetMana();
    PentagramData_T currentPentagram = m_MoveSet.GetMove(currentMana - 1);

    m_CasterManager.SetPentagramData(currentPentagram);

    int spellCost = m_CasterManager.GetSpellCost();
    bool canCast = m_CasterManager.CanCastSpell();

    for (int i = currentMana; !canCast && i > 0; i--)
    {
        currentPentagram = m_MoveSet.GetMove(currentMana - 1);
        m_CasterManager.SetPentagramData(currentPentagram);
        canCast = m_CasterManager.CanCastSpell();
    }

    if (currentMana > 0)
    {
        m_CasterManager.GetSpellDetail()->isHidden = true;
        CastSpell();
    }
    else
    {
        EndTurn(true);
    }
}
