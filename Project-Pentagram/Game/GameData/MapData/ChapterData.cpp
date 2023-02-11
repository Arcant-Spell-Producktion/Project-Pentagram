#include "ChapterData.h"

ChapterData::ChapterData()
{
}

void ChapterData::AddNode(NodeData* n)
{
    m_Nodes.push_back(n);
    m_NodeCount++;
}

ChapterData::~ChapterData()
{
    for (size_t i = 0; i < m_NodeCount; i++)
    {
        delete m_Nodes[i];
    }
}
