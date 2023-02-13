#include "MapData.h"

MapData::MapData(Element::Type startElement)
{
    for (size_t i = (int)Element::NULLTYPE; i < (int)Element::Wind; i++)
    {
        Element::Type element = static_cast<Element::Type>(i);
        ChapterData* chapter = new ChapterData(element,startElement);
        AddChapter(chapter);
    }
}

void MapData::AddChapter(ChapterData* c)
{
    m_Chapters.emplace(c->Element(),c);
}

bool MapData::CanVisitChapter(Element::Type element)
{
    return m_Chapters[element]->CanVisit();
}

void MapData::SelectChapter(Element::Type element)
{
    if (CanVisitChapter(element))
    {
        m_CurrentChapter = element;
    }
}



MapData::~MapData()
{
    for (auto chapter : m_Chapters)
    {
        delete chapter.second;
    }
    m_Chapters.clear();
}

bool MapData::CompleteNode()
{
    return m_Chapters[m_CurrentChapter]->CompleteNode();
}

NodeData* MapData::GetNextNode()
{
    return m_Chapters[m_CurrentChapter]->GetNextNode();
}
