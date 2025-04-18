#pragma once
#include "Engine/IGameObjectManager.h"
#include "PentagramScrollButton.h"
#include <Game/BattleScene/SpellCaster/PentagramData.h>

class PentagramScrollButtonManagerUI :public UIObject
{
private:
    PentagramField m_CurrentField = PentagramField::Time;

    UIObject* m_Scroll;
    std::vector<PentagramScrollNumberButton*> m_IntButtons;
    std::vector<PentagramScrollArrowButton*> m_ArrowButtons;

    void SetToggle(int i);
    void SetScrollMode(PentagramField field);
public:
    Event<int> OnScrollButtonClicked;

    void SetScrollMode(PentagramEvent e);

    PentagramScrollButtonManagerUI(IGameObjectManager* scene);

    
};