﻿#pragma once
#include "ChapterData.h"
#include <bitset>
#include <array>

#include <map>

struct MapSaveData
{
    bool isAtMap;
    int completeChapter;
    int currentChapterElement;
    std::array<int, 5> nodeIndex;
    std::array<bool,5> canVisit;
};

class MapData
{
private:
    int m_CompleteChapterCount = 0;
    Element::Type m_StartElement;
    Element::Type m_CurrentChapter;
    std::map<Element::Type,ChapterData*> m_Chapters;

    NodeData* m_CurrentNode = nullptr;

public:
    bool IsAtMap = false;

    MapData(Element::Type startElement);

    Element::Type GetCurrentChapter() {
        return m_CurrentChapter;
    }

    void AddChapter(ChapterData* c);

    bool IsChapterComplete(Element::Type element);

    bool CanVisitChapter(Element::Type element);

    void SelectChapter(Element::Type element);

    NodeData* GetNextNode();

    bool CompleteNode();

    MapSaveData SaveMapData();

    void LoadMapData(MapSaveData data);

    ~MapData();
};


