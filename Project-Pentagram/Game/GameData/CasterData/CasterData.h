#pragma once
#include "Game/Spells/Element.h"
#include "CasterPosition.h"
#include "CasterStat.h"

class CasterData
{
private:
    CasterStat m_Stat;
    Element::Type m_Element;
    CasterPosition m_Position;
public:
    CasterData(CasterStat stat,Element::Type element = Element::NULLTYPE, CasterPosition position = CasterPosition::NONE) :
        m_Stat(stat),
        m_Element(element),
        m_Position(position)
    {}

    CasterData(const CasterData &casterData):
        m_Element(casterData.m_Element),
        m_Position(casterData.m_Position),
        m_Stat(casterData.m_Stat)
    {}
    
    CasterData& operator()(CasterStat stat, Element::Type element = Element::NULLTYPE, CasterPosition position = CasterPosition::NONE)
    {
        m_Stat = stat;
        m_Element = element;
        m_Position = position;

        return *this;
    }

    Element::Type& Element() { return m_Element; }

    CasterPosition& Position() { return m_Position; }

    CasterStat& Stat() { return m_Stat; }
};
