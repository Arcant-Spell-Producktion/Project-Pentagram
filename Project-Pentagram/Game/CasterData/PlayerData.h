#pragma once
#include "Utilities/Singleton.h"
#include "Game/Spells/Element.h"
class PlayerData:public Singleton<PlayerData>
{
private:
    Element::Type m_Element = Element::NULLTYPE;
    int m_PlayerHealth = 0;
    int m_PlayerMana = 0;
public:
    void Init(Element::Type element, int health, int mana)
    {
        m_Element = element;
        m_PlayerHealth = health;
        m_PlayerMana = mana;
    };

    Element::Type GetPlayerElement() { return m_Element; }

    int GetPlayerMaxHealth() { return m_PlayerHealth; }

    int GetPlayerMaxMana() { return m_PlayerMana; }
};

