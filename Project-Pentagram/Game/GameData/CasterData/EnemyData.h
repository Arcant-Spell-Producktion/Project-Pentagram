#pragma once
#include "CasterData.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"
#include <array>
class EnemyData : public CasterData
{
private:
    CasterType m_Type;

public:
    EnemyData(CasterData data,CasterType type) :
        CasterData(data),m_Type(type)
    {
        m_Position = CasterPosition::CasterB;
    }

    EnemyData(const EnemyData& enemyData) :
        CasterData(enemyData),
        m_Type(enemyData.m_Type)
    {}

    CasterType EnemyType() { return m_Type; }
};

class EnemyMoveSet
{
private:
    std::array<PentagramData_T,20> m_MoveSet;

public:
    EnemyMoveSet(std::array<PentagramData_T,20> moveSet):m_MoveSet(moveSet)
    {
        
    }

    PentagramData_T GetMove(int index)
    {
        return m_MoveSet[index];
    }
};

class TestMoveSet : public EnemyMoveSet
{
public:
    TestMoveSet() :EnemyMoveSet(std::array<PentagramData_T, 20>{ {
        {1, 1, 1, 1, 2},
        { 1, 1, 1, 1, 1 },
        { 2, 1, 1, 1, 1 },
        { 1, 2, 1, 1, 1 },
        { 2, 2, 1, 1, 1 },
        { 2, 2, 1, 1, 1 },
        { 2, 2, 1, 1, 1 },
        { 3, 1, 1, 1, 1 },
        { 1, 3, 1, 1, 1 },
        { 1, 3, 1, 1, 1 },
        { 3, 1, 1, 1, 1 },
        { 1, 3, 1, 1, 1 },
        { 1, 2, 1, 1, 1 },
        { 2, 1, 1, 1, 1 },
        { 3, 1, 1, 1, 1 },
        { 2, 1, 1, 1, 1 },
        { 3, 1, 1, 1, 1 },
        { 2, 1, 1, 1, 1 },
        { 3, 1, 1, 1, 1 },
        { 1, 3, 1, 1, 1 }}}
    )
    {}
};