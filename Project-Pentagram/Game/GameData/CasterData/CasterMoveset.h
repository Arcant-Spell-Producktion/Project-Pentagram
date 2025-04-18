#pragma once
#include <array>
#include "Game/BattleScene/SpellCaster/PentagramData.h"

#define CASTER_MOVESET_SIZE 25

class CasterMoveSet
{
private:
    std::array<PentagramData_T, CASTER_MOVESET_SIZE> m_MoveSet;

public:
    CasterMoveSet()
    {
        
    }

    CasterMoveSet(std::array<PentagramData_T, CASTER_MOVESET_SIZE> moveSet) :m_MoveSet(moveSet)
    {

    }

    void SetMove(int index,PentagramData_T data)
    {
        m_MoveSet[index] = data;
    }

    PentagramData_T GetMove(int index)
    {
        return m_MoveSet[index];
    }
};
