#pragma once
#include "ChapterData.h"
class MapData
{
private:
    int m_MapPos = 0;
    int m_ChapterCount = 0;
    std::vector<ChapterData*> m_Chapters;

public:
    MapData();

    void AddChapter(ChapterData* c);

    ~MapData();
};