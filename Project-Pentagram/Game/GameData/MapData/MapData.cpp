#include "MapData.h"

MapData::MapData()
{
    
}

void MapData::AddChapter(ChapterData* c)
{
    m_Chapters.push_back(c);
    m_ChapterCount++;
}

MapData::~MapData()
{
    for (size_t i = 0; i < m_ChapterCount; i++)
    {
        delete m_Chapters[i];
    }
}
