#pragma once
#include "CasterData.h"

class EnemyData : public CasterData
{
private:
    CasterPosition m_Position = CasterPosition::CasterB;
    CasterType m_Type;

public:
    EnemyData(CasterData data,CasterType type) :
        CasterData(data),m_Type(type)
    {
    }
};

