#pragma once
#include <map>
#include <vector>
#include "Game/GameData/CasterData/EnemyData.h"
#include "Utilities/Singleton.h"

class CasterStatList
{
private:
    std::vector<CasterStat> m_Levels;
    int m_MaxLvl = 0;
public:
    CasterStatList() {}

    CasterStat GetStatByLv(int lvl)
    {
        int _lvl = lvl < 0 ? 0 : lvl < m_MaxLvl ? lvl : m_MaxLvl;
        return m_Levels[_lvl];
    }

    void Add(CasterStat stat) {
        m_MaxLvl++;
        m_Levels.push_back(stat);
    }
};

class CasterStatTable
{
private:
    std::map<CasterType, CasterStatList*> Lists;

public:
    CasterStatTable() {}

    void Add(CasterType type , CasterStat stat) {

        if (!Lists.count(type))
        {
            Lists.emplace(type, new CasterStatList());
        }

        Lists[type]->Add(stat);
    }

    CasterStatList* GetCasterStatList(CasterType type)
    {
        if (Lists.count(type))
        {
            return Lists[type];
        }

        return nullptr;
    }

    ~CasterStatTable()
    {
        for (auto list : Lists)
        {
            delete(list.second);
        }

        Lists.clear();
    }

};

class CasterStatDatabase :public Singleton<CasterStatDatabase>
{
private:
    std::map<Element::Type, CasterStatTable*> CasterStatTables;
public:
    void LoadResource();

    void Add(Element::Type element, CasterType type, CasterStat stat);

    CasterStat GetStat(Element::Type element, CasterType type, int level)
    {
        return CasterStatTables[element]->GetCasterStatList(type)->GetStatByLv(level);
    };

    ~CasterStatDatabase()
    {
        for (auto table: CasterStatTables)
        {
            delete(table.second);
        }

        CasterStatTables.clear();
    }
};
