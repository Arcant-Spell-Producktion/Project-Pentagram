#pragma once
#include "NodeData.h"

class ChapterData
{
private:
    int m_NodeCount = 0;
    int m_CurrentNode = 0;
    Element::Type m_Element;
    std::vector<NodeData*> m_Nodes;
    bool m_IsVisited;

    void AddNode(NodeData* node);
public:

    bool CanVisit;

    ChapterData(Element::Type element, Element::Type startElement);

    Element::Type Element() { return m_Element; }

    NodeData* GetNextNode();

    //true if chapter is complete
    bool CompleteNode();

    void UpdateChapter(int level);

    ~ChapterData();
};
