#include "NodeData.h"

NodeData::NodeData(EnemyData enemy) : m_Enemy(enemy)
{
    m_IsCompleted = false;
}

void NodeData::CompleteNode()
{
    m_IsCompleted = true;
}
