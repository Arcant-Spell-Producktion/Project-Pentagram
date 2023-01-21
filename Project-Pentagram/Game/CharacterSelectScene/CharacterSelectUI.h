#pragma once
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/GameObject/CasterObject.h"
#include "Game/Objects/ScrollButton.h"
class CharacterSelectUI : public UIObject
{
private:
    ScrollButton* m_SelectButton = nullptr;
    CasterObject* m_Caster = nullptr;

public:
    Event<Element::Type> OnCharacterSelect;

    CharacterSelectUI(Element::Type element);

    void Select();

    void Deselect();

    void Confirm();
};