#pragma once
#include <map>
#include <vector>
#include "Game/GameData/CasterData/EnemyData.h"
#include "Utilities/Singleton.h"

class CasterMoveSetList
{
private:
    std::vector<CasterMoveSet> m_Levels;
    int m_MaxLvl = 0;
public:
    CasterMoveSetList() {}

    CasterMoveSet GetMoveSetByLv(int lvl)
    {
        int _lvl = lvl < 0 ? 0 : lvl < m_MaxLvl ? lvl : m_MaxLvl;
        return m_Levels[_lvl];
    }

    void Add(CasterMoveSet MoveSet) {
        m_MaxLvl++;
        m_Levels.push_back(MoveSet);
    }
};

class CasterMoveSetTable
{
private:
    std::map<CasterType, CasterMoveSetList*> Lists;

public:
    CasterMoveSetTable() {}

    void Add(CasterType type , CasterMoveSet MoveSet) {

        if (!Lists.count(type))
        {
            Lists.emplace(type, new CasterMoveSetList());
        }

        Lists[type]->Add(MoveSet);
    }

    CasterMoveSetList* GetCasterMoveSetList(CasterType type)
    {
        if (Lists.count(type))
        {
            return Lists[type];
        }

        return nullptr;
    }

    ~CasterMoveSetTable()
    {
        for (auto list : Lists)
        {
            delete(list.second);
        }

        Lists.clear();
    }

};

class CasterMoveSetDatabase :public Singleton<CasterMoveSetDatabase>
{
private:
    std::map<Element::Type, CasterMoveSetTable*> CasterMoveSetTables;

public:
    void LoadResource();

    void Add(Element::Type element, CasterType type, CasterMoveSet MoveSet);

    CasterMoveSet GetMoveSet(Element::Type element, CasterType type, int level)
    {
        return CasterMoveSetTables[element]->GetCasterMoveSetList(type)->GetMoveSetByLv(level);
    };

    ~CasterMoveSetDatabase()
    {
        for (auto table: CasterMoveSetTables)
        {
            delete(table.second);
        }

        CasterMoveSetTables.clear();
    }
};
