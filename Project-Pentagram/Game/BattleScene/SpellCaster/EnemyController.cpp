#include "EnemyController.h"

void EnemyController::CastEnemySpell()
{
    int currentMana = m_CasterManager.GetMana();
    PentagramData_T currentPentagram = m_MoveSet.GetMove(currentMana - 1);
    m_CasterManager.SetPentagramData(currentPentagram);

    bool canCast = m_CasterManager.CanCastSpell();

    while (!canCast && currentMana > 0)
    {
        if(m_CasterManager.IsTrackFull())
        {
            bool changeSpell = false;
            while (m_CasterManager.IsTrackFull())
            {
                currentPentagram.time += 1;
                m_CasterManager.SetPentagramData(currentPentagram);

                if (m_CasterManager.IsTrackFull() && currentPentagram.time > 11)
                {
                    changeSpell = true;
                    currentMana--;
                    currentPentagram = m_MoveSet.GetMove(currentMana - 1);
                    m_CasterManager.SetPentagramData(currentPentagram);
                    break;
                }
            }

            if (changeSpell)
            {
                continue;
            }
        }

        if(!m_CasterManager.HaveEnoughMana())
        {
            currentMana--;

            currentPentagram = m_MoveSet.GetMove(currentMana - 1);
            m_CasterManager.SetPentagramData(currentPentagram);
        }

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

void EnemyController::CastEnemySpell(PentagramData_T pentagram)
{
    m_CasterManager.SetPentagramData(pentagram);
    m_CasterManager.GetSpellDetail()->isHidden = true;
    CastSpell();
}
