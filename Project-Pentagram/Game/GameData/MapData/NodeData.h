#pragma once
#include <vector>
#include "Game/GameData/CasterData/EnemyData.h"
class NodeData
{
private:
    EnemyData m_Enemy;

    bool m_IsCompleted;
public:
    NodeData(EnemyData enemy);

    EnemyData& GetEnemyData() { return m_Enemy; }

    void CompleteNode();
};
