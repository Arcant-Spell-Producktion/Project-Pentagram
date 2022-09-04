#pragma once
#include <vector>
#include "Game/GameData/CasterData/EnemyData.h"
class MapData
{
private:
    int m_MapPos;
    std::vector<EnemyData> m_EnemyList;
};