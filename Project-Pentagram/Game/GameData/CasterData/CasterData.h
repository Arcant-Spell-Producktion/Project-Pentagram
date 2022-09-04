#pragma once
#include "Game/Spells/Element.h"
#include "CasterPosition.h"

class CasterData
{
private:
    Element::Type m_Element = Element::NULLTYPE;
    CasterPosition m_Position = CasterPosition::NONE;
    int m_Health = 10;
    int m_Mana = 10;
public:
    CasterData(Element::Type element = Element::NULLTYPE, int health = 10, int mana = 10):
        m_Element(element),
        m_Health(health),
        m_Mana(mana)
    {}

    CasterData(const CasterData &casterData):
        m_Element(casterData.m_Element),
        m_Health(casterData.m_Health),
        m_Mana(casterData.m_Mana)
    {}

    CasterData& operator()(Element::Type element = Element::NULLTYPE, int health = 10, int mana = 10)
    {
        m_Element = element;
        m_Health = health;
        m_Mana = mana;
        return *this;
    }

    Element::Type GetElement() { return m_Element; }

    void SetElement(Element::Type element) { m_Element = element; }

    virtual CasterPosition GetPosition() { return m_Position; }

    void SetPosition(CasterPosition position) { m_Position = position; }
    
    int GetHealth() { return m_Health; }

    void SetHealth(int health) { m_Health = health; }

    int GetMana() { return m_Mana; }

    void SetMana(int mana) { m_Mana = mana; }
};

