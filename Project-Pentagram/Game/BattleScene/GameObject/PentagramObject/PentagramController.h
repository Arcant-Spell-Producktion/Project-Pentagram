#pragma once
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/GameObject/SpellIconUI.h"
#include "Game/Objects/ScrollButton.h"

#include "Game/BattleScene/SpellCaster/CasterController.h"

#include "PentagramCircleUI.h"
#include "PentagramFieldButtonManagerUI.h"
#include "PentagramScrollButtonManagerUI.h"

class PentragramController
{
private:

    IGameObjectManager* m_ObjectManager;

    CasterController* m_currentCaster = nullptr;
    PentagramData_T m_currentData = {1,1,1,1,0};

    PentagramField m_currentField = PentagramField::Time;

    PentagramCircleUI* m_PentragramCircle;
    PentagramFieldButtonUI* m_PentragramFieldButtons;
    PentagramScrollButtonManagerUI* m_PentagramScrollButton;

    ScrollButton* m_CastButton;
    ScrollButton* m_PassButton;

    UIObject* m_Scroll_2;

    SpellIconUI* m_SpellIcon;

    int& FieldData(PentagramField field);

    Event<PentagramField> OnPentagramFieldChange;
    Event<PentagramEvent> OnPentagramValueChange;
public:

    Event<PentagramData_T&> OnPentagramDataChange;

    PentragramController(IGameObjectManager* scene);

    void SetActive(const bool& active);

    void SetPentagramField(PentagramField selectedField);

    void SetPentagramValue(int value);
    
    void SetCastButtonActive(bool isActive) { m_CastButton->SetActive(isActive); }

    void SetPentagramOwner(CasterController* caster);

    void ResetPentagram();
    void ResetPentagramButtonField();

};