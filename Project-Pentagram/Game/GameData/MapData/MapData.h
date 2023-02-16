#pragma once
#include "ChapterData.h"
#include <map>
class MapData
{
private:
    Element::Type m_StartElement;
    Element::Type m_CurrentChapter;
    std::map<Element::Type,ChapterData*> m_Chapters;

public:
    MapData(Element::Type startElement);

    void AddChapter(ChapterData* c);

    bool CanVisitChapter(Element::Type element);

    void SelectChapter(Element::Type element);

    NodeData* GetNextNode();

    bool CompleteNode();

    ~MapData();
};
