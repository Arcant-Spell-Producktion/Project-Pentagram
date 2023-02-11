#pragma once
#include "NodeData.h"

class ChapterData
{
private:
    int m_NodeCount = 0;
    Element::Type m_Element;
    std::vector<NodeData*> m_Nodes;

public:
    ChapterData();

    void AddNode(NodeData* node);

    ~ChapterData();
};
