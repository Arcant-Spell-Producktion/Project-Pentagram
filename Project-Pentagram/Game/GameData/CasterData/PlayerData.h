#pragma once
#include "CasterData.h"

struct PlayerSaveData
{
    int element_index;
    int level;
    int hp;
};

class PlayerData: public CasterData  
{
private:
    int m_Level = 0;
public:
    PlayerData(CasterData data,int level = 0) :
        CasterData(data)
    {
        SetPlayerLevel(level);
    }
    void LevelUp();

    void SetPlayerLevel(int level);

    PlayerSaveData SavePlayerData();
};

