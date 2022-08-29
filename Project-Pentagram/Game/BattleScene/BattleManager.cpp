#include "BattleManager.h"

void BattleManager::AddCaster()
{
    CasterController* newCaster = new CasterController();
    m_Casters.push_back(newCaster);
}

CasterController* BattleManager::ChangeNextCaster()
{
    int currentCasterIndex = std::find(m_Casters.begin(), m_Casters.end(),m_CurrentCaster) - m_Casters.begin();
    int nextCasterIndex = (currentCasterIndex + 1) % m_Casters.size();
    m_CurrentCaster = m_Casters[nextCasterIndex];
    return m_CurrentCaster;
}

BattleManager::~BattleManager()
{
    for(CasterController* cc : m_Casters)
    {
        delete cc;
    }
    m_Casters.clear();
}
