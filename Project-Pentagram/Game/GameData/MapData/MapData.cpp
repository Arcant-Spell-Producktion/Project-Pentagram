#include "MapData.h"
#include <iostream>
MapData::MapData(Element::Type startElement):m_StartElement(startElement)
{
    for (int i = (int)Element::Earth; i <= (int)Element::Corrupt; i++)
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

    m_Chapters[m_StartElement]->CompleteChapter();
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
        m_CompleteChapterCount++;

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

        m_Chapters[Element::Corrupt]->CanVisit = true;

        for (int i = 0; i < 4; ++i)
        {
            Element::Type e = static_cast<Element::Type>(i);
            ChapterData* chapter = m_Chapters[e];
            if (chapter->CanVisit)
            {
                chapter->UpdateChapter(m_CompleteChapterCount);
            }
        }
    }
    return isChapterComplete;
}

MapSaveData MapData::SaveMapData()
{
    MapSaveData data;
    data.completeChapter = m_CompleteChapterCount;
    data.currentChapterElement = (int)m_CurrentChapter;
    for (int i = 0; i < 4; ++i)
    {
        ChapterData* chapter = m_Chapters[static_cast<Element::Type>(i)];
        data.nodeIndex[i] = chapter->GetCurrentNode();
        data.canVisit[i] = chapter->CanVisit;
    }
    return data;
}

void MapData::LoadMapData(MapSaveData data)
{
    m_CompleteChapterCount = data.completeChapter;
    m_CurrentChapter = static_cast<Element::Type>(data.currentChapterElement);
    for (int i = 0; i < 4; ++i)
    {
        ChapterData* chapter = m_Chapters[static_cast<Element::Type>(i)];
        chapter->CanVisit = data.canVisit[i];
        chapter->SetCurrentNode(data.nodeIndex[i]);
        if(chapter->CanVisit) chapter->UpdateChapter(m_CompleteChapterCount);
    }
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
