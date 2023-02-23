#include "ChapterData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/GameData/CasterData/CasterMovesetDatabase.h"
#include <stdexcept>
#include <iostream>

#define NODE_PER_CHAPTER 3

ChapterData::ChapterData(Element::Type element, Element::Type startElement)
{
    m_Element = element;
    m_IsVisited = false;

    if (element == startElement)
    {
        CanVisit = false;
        m_IsVisited = true;
    }

    UpdateChapter(0);
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
    m_IsVisited = true;
    m_CurrentNode++;
    return m_NodeCount == m_CurrentNode;
}

void ChapterData::UpdateChapter(int level)
{
    CasterStatDatabase* casterDB = CasterStatDatabase::GetInstance();

    if (m_Element == Element::NULLTYPE)
    {
        return; // TODO:: implement after big boss is here

    /*    NodeData* node = nullptr;
        CasterStat stat = casterDB->GetStat(m_Element, CasterType::BigBoss, 0);
        CasterData data(stat, m_Element, CasterPosition::CasterB);
        EnemyData enemy(data, CasterType::BigBoss);
        try {
            node = m_Nodes.at(0);
            node->GetEnemyData() = enemy;
        }
        catch (const std::out_of_range& e) {
            node = new NodeData(enemy);
            AddNode(node);
        }*/
    }

    for (size_t i = 0; i < NODE_PER_CHAPTER; i++)
    {
        bool isMinion =(i != (NODE_PER_CHAPTER - 1));
        NodeData* node = nullptr;
        CasterType type = isMinion ? CasterType::Minion : CasterType::Boss;
        int type_level = isMinion ? level + i : level;

        CasterStat stat = casterDB->GetStat(m_Element, type , type_level);
        CasterMoveSet moves = CasterMoveSetDatabase::GetInstance()->GetMoveSet(m_Element, type, type_level);

        CasterData data(stat,m_Element,CasterPosition::CasterB);
        EnemyData enemy(data, type, moves);
        try {
            node = m_Nodes.at(i);
            node->GetEnemyData() = enemy;
        }
        catch (const std::out_of_range& e) {
            node = new NodeData(enemy);
            AddNode(node);
        }
    }
   
}

ChapterData::~ChapterData()
{
    for (size_t i = 0; i < m_NodeCount; i++)
    {
        delete m_Nodes[i];
    }
}
