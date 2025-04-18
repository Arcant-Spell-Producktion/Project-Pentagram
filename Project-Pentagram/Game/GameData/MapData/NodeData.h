#pragma once
#include <vector>
#include "Game/GameData/CasterData/EnemyData.h"
class NodeData
{
protected:
    EnemyData m_Enemy;

    bool m_IsCompleted;
public:
    NodeData(EnemyData enemy);

    EnemyData GetEnemyData() { return m_Enemy; }

    void SetEnemyData(EnemyData enemy) { m_Enemy = enemy; }

    void CompleteNode();
};
