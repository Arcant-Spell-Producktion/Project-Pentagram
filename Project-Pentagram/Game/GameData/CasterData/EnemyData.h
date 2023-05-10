#pragma once
#include "CasterData.h"
#include "CasterMoveSet.h"
#include <map>
class EnemyData : public CasterData
{
private:
    std::map<Element::Type, CasterMoveSet> m_ElementMoveSet;

    CasterMoveSet m_Moves;
protected:
    CasterType m_Type;

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

    void SetMove(Element::Type element ,CasterMoveSet moves)
    {
        m_ElementMoveSet[element] = moves;
    }

    CasterType EnemyType() { return m_Type; }

    CasterMoveSet EnemyMoves() { return m_Moves; }

    CasterMoveSet EnemyMoves(Element::Type element) { return m_ElementMoveSet[element]; }

};

