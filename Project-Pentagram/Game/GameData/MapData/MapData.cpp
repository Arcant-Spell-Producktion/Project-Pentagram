#include "MapData.h"
#include <iostream>
MapData::MapData(Element::Type startElement):m_StartElement(startElement)
{
    for (int i = (int)Element::NULLTYPE; i <= (int)Element::Wind; i++)
    {
        Element::Type element = static_cast<Element::Type>(i);
        ChapterData* chapter = new ChapterData(element, m_StartElement);
        AddChapter(chapter);
    }

    switch (m_StartElement)
    {
    case Element::Earth:
    case Element::Fire:
        m_Chapters[Element::Water]->CanVisit = true;
        m_Chapters[Element::Wind]->CanVisit = true;
        break;
    case Element::Water:
    case Element::Wind:
        m_Chapters[Element::Earth]->CanVisit = true;
        m_Chapters[Element::Fire]->CanVisit = true;
        break;
    }
}

void MapData::AddChapter(ChapterData* c)
{
    m_Chapters.emplace(c->Element(),c);
}

bool MapData::CanVisitChapter(Element::Type element)
{
    return m_Chapters[element]->CanVisit;
}

void MapData::SelectChapter(Element::Type element)
{
    if (CanVisitChapter(element))
    {
        m_CurrentChapter = element;
    }
}

bool MapData::CompleteNode()
{
    bool isChapterComplete = m_Chapters[m_CurrentChapter]->CompleteNode();
    if (isChapterComplete)
    {
        switch (m_StartElement)
        {
        case Element::Earth:
            m_Chapters[Element::Fire]->CanVisit = true;
            break;
        case Element::Fire:
            m_Chapters[Element::Earth]->CanVisit = true;
            break;
        case Element::Water:
            m_Chapters[Element::Wind]->CanVisit = true;
            break;
        case Element::Wind:
            m_Chapters[Element::Water]->CanVisit = true;
            break;
        }

        m_Chapters[Element::NULLTYPE]->CanVisit = true;
    }
    return isChapterComplete;
}

NodeData* MapData::GetNextNode()
{
    std::cout << "Chapter: " << (int)m_CurrentChapter << "\n";

    return m_Chapters[m_CurrentChapter]->GetNextNode();
}

MapData::~MapData()
{
    for (auto chapter : m_Chapters)
    {
        delete chapter.second;
    }
    m_Chapters.clear();
}
