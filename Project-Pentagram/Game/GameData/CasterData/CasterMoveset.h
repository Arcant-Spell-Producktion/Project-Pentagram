#pragma once
#include <array>
#include "Game/BattleScene/SpellCaster/PentagramData.h"

class CasterMoveSet
{
private:
    std::array<PentagramData_T, 20> m_MoveSet;

public:
    CasterMoveSet()
    {
        
    }

    CasterMoveSet(std::array<PentagramData_T, 20> moveSet) :m_MoveSet(moveSet)
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
