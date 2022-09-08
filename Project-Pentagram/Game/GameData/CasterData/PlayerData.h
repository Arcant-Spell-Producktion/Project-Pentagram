#pragma once
#include "CasterData.h"

class PlayerData: public CasterData  
{
private:
    int m_Level;
public:
    PlayerData(CasterData data,int level = 1) :
        CasterData(data),
        m_Level(level)
    {
    }
};