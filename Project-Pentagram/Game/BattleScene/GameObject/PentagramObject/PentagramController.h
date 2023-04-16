#pragma once
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/GameObject/SpellIconUI.h"
#include "Game/Objects/ScrollButton.h"

#include "Game/BattleScene/SpellCaster/CasterController.h"

#include "PentagramCircleUI.h"
#include "PentagramFieldButtonManagerUI.h"
#include "PentagramScrollButtonManagerUI.h"
#include "Game/BattleScene/GameObject/MainObjectEnum.h"

class PentragramController
{
private:

    Event<PentagramField> OnPentagramFieldChange;
    Event<PentagramEvent> OnPentagramValueChange;

    PentagramEvent m_LastestEvent = {PentagramField::Time,0};
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
    void TogglePentagramField(PentagramField field, bool isActive);
public:

    Event<PentagramData_T&> OnPentagramDataChange;
    

    PentragramController(IGameObjectManager* scene);


    void SetPentagramData(PentagramData_T data);

    void SetActive(const bool& active);

    void SetPentagramField(PentagramField selectedField);

    void SetPentagramValue(int value);
    
    void SetCastButtonActive(bool isActive) { m_CastButton->SetActive(isActive); }

    void SetPentagramOwner(CasterController* caster);

    void SetPentagramActive(MainObjectEnum obj,const bool& isActive);

    void ResetPentagram();
    void ResetPentagramButtonField();

    GameObject* GetPentagramObject(MainObjectEnum obj) const;
};