#pragma once
#include "NodeData.h"

class ChapterData
{
private:
    int m_NodeCount = 0;
    Element::Type m_Element;
    std::vector<NodeData*> m_Nodes;

    int m_CurrentNode = 0;

    void ClearNode();

    void AddNode(NodeData* node);
public:

    bool IsCompleted;
    bool CanVisit;

    ChapterData(Element::Type element, Element::Type startElement);

    Element::Type Element() { return m_Element; }

    int GetCurrentNode () { return m_CurrentNode; }

    void SetCurrentNode(int node)
    {
        m_CurrentNode = node;
        IsCompleted = m_NodeCount == m_CurrentNode;
    }

    NodeData* GetNextNode();

    //true if chapter is complete
    bool CompleteNode();

    void CompleteChapter();

    void UpdateChapter(int level);

    ~ChapterData();
};
