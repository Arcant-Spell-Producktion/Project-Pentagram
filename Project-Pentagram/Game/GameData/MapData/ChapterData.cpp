#include "ChapterData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"
#include <stdexcept>
#include <iostream>

#define NODE_PER_CHAPTER 3

ChapterData::ChapterData(Element::Type element, Element::Type startElement)
{
    m_Element = element;
    m_IsCompleted = false;

    if (element == startElement)
    {
        CanVisit = false;
        m_IsCompleted = true;
    }

    UpdateChapter(0);
}

void ChapterData::ClearNode()
{
    for (size_t i = 0; i < m_NodeCount; i++)
    {
        delete m_Nodes[i];
    }
}

void ChapterData::AddNode(NodeData* n)
{
    m_Nodes.push_back(n);
    m_NodeCount++;

    std::cout << "Add new node #" << m_NodeCount << "\n";
}

NodeData* ChapterData::GetNextNode()
{
    return m_Nodes[m_CurrentNode];
}

bool ChapterData::CompleteNode()
{
    CanVisit = false;
    m_CurrentNode++;
    m_IsCompleted = m_NodeCount == m_CurrentNode;
    return m_IsCompleted;
}

void ChapterData::CompleteChapter()
{
    CanVisit = false;
    m_CurrentNode = m_NodeCount;
    m_IsCompleted = true;
}

void ChapterData::UpdateChapter(int level)
{
    CasterStatDatabase& casterDB = CasterStatDatabase::GetInstance();

    if (m_Element == Element::Corrupt)
    {
        NodeData* node = nullptr;
        CasterStat stat = casterDB.GetStat(m_Element, CasterType::BigBoss, 0);
        CasterData data(stat, m_Element, CasterPosition::CasterB);

        CasterMoveSet moveE = CasterMoveSetDatabase::GetInstance().GetMoveSet(Element::Earth, CasterType::BigBoss, level);

        EnemyData enemy(data, CasterType::BigBoss, moveE);

        for (int i = static_cast<int>(Element::Earth); i <= static_cast<int>(Element::Wind);i++)
        {
            Element::Type e = static_cast<Element::Type>(i);
            enemy.SetMove(e, CasterMoveSetDatabase::GetInstance().GetMoveSet(e, CasterType::BigBoss, level));
        }

        try {
            node = m_Nodes.at(0);
            node->GetEnemyData() = enemy;
        }
        catch (const std::out_of_range& e) {
            node = new NodeData(enemy);
            AddNode(node);
        }

        return;
    }

    for (size_t i = 0; i < NODE_PER_CHAPTER; i++)
    {
        bool isMinion =(i != (NODE_PER_CHAPTER - 1));
        NodeData* node = nullptr;
        CasterType type = isMinion ? CasterType::Minion : CasterType::Boss;
        int type_level = isMinion ? level * 2 + i : level;

        CasterStat stat = casterDB.GetStat(m_Element, type , type_level);
        CasterMoveSet moves = CasterMoveSetDatabase::GetInstance().GetMoveSet(m_Element, type, type_level);

        CasterData data(stat,m_Element,CasterPosition::CasterB);
        EnemyData enemy(data, type, moves);
        try {
            node = m_Nodes.at(i);
            node->SetEnemyData(enemy);
        }
        catch (const std::out_of_range& e) {
            node = new NodeData(enemy);
            AddNode(node);
        }
    }
   
}

ChapterData::~ChapterData()
{
    ClearNode();
}
