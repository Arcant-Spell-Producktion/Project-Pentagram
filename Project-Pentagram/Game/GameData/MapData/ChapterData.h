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
    bool m_CanVisit;

    void AddNode(NodeData* node);
public:
    ChapterData(Element::Type element, Element::Type startElement);

    Element::Type Element() { return m_Element; }

    bool CanVisit() { return m_CanVisit; }

    NodeData* GetNextNode();

    //true if chapter is complete
    bool CompleteNode();

    void UpdateChapter(int level);

    ~ChapterData();
};
