#pragma once
#include "CasterData.h"

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
};

