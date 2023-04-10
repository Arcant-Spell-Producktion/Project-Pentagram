#pragma once
#include "CasterData.h"
#include "CasterMoveSet.h"

class EnemyData : public CasterData
{
private:
    CasterType m_Type;
    CasterMoveSet m_Moves;

public:
    EnemyData(CasterData data,CasterType type, CasterMoveSet moves) :
        CasterData(data),m_Type(type),m_Moves(moves)
    {
        m_Position = CasterPosition::CasterB;
    }

    EnemyData(const EnemyData& enemyData) :
        CasterData(enemyData),
        m_Type(enemyData.m_Type),
        m_Moves(enemyData.m_Moves)
    {}

    void SetMove(CasterMoveSet moves) { m_Moves = moves; }

    CasterType EnemyType() { return m_Type; }

    CasterMoveSet EnemyMoves() { return m_Moves; }
};

