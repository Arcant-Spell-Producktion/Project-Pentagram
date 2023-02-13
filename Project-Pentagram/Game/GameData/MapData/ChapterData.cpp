#include "ChapterData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include <stdexcept>

#define NODE_PER_CHAPTER 3

ChapterData::ChapterData(Element::Type element, Element::Type startElement)
{
    m_Element = element;
    m_IsVisited = false;

    if (element == startElement)
    {
        m_CanVisit = false;
        m_IsVisited = true;
    }
    else if (element == Element::NULLTYPE)
    {
        m_CanVisit = true;
    }
    else
    {
        if ((startElement == Element::Fire && (element == Element::Wind || element == Element::Earth)) ||
            (startElement == Element::Water && (element == Element::Fire || element == Element::Earth)) ||
            (startElement == Element::Earth && (element == Element::Wind || element == Element::Fire)) ||
            (startElement == Element::Wind && (element == Element::Earth || element == Element::Water)))
        {
            m_CanVisit = true;
        }
        else
        {
            m_CanVisit = false;
        }
    }

    UpdateChapter(0);
}

void ChapterData::AddNode(NodeData* n)
{
    m_Nodes.push_back(n);
    m_NodeCount++;
}

NodeData* ChapterData::GetNextNode()
{
    return m_Nodes[m_CurrentNode];
}

bool ChapterData::CompleteNode()
{
    m_CanVisit = false;
    m_IsVisited = true;
    m_NodeCount++;
    return m_NodeCount == m_CurrentNode;
}

void ChapterData::UpdateChapter(int level)
{
    CasterStatDatabase* casterDB = CasterStatDatabase::GetInstance();

    if (m_Element == Element::NULLTYPE)
    {
        return; // TODO:: implement after big boss is here

        NodeData* node = nullptr;
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
        }
    }

    for (size_t i = 0; i < NODE_PER_CHAPTER; i++)
    {
        bool isMinion =(i != (NODE_PER_CHAPTER - 1));
        NodeData* node = nullptr;
        CasterStat stat = casterDB->GetStat(m_Element, isMinion ? CasterType::Minion : CasterType::Boss, isMinion ? level + i : level);
        CasterData data(stat,m_Element,CasterPosition::CasterB);
        EnemyData enemy(data, isMinion ? CasterType::Minion : CasterType::Boss);
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
