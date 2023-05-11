#include "PlayerData.h"

#include "CasterStatDatabase.h"

void PlayerData::LevelUp()
{
    SetPlayerLevel(m_Level + 1);
}

void PlayerData::SetPlayerLevel(int level)
{
    m_Level = level;
    if (m_Level > 2) m_Level = 2;
    m_Stat = CasterStatDatabase::GetInstance().GetStat(m_Element, CasterType::Player, level);
}

PlayerSaveData PlayerData::SavePlayerData()
{
    PlayerSaveData save_data;

    save_data.element_index = static_cast<int>(m_Element);
    save_data.level = m_Level;
    save_data.hp = m_Stat.CurrentHealth;

    return save_data;
}

