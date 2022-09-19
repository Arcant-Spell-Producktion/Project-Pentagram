#pragma once
#include <vector>
#include "Game/BattleScene/BattleScene.h"
#include <Game/BattleScene/SpellCaster/PentagramData.h>

class PentragramController: public GameObject
{
private:
    BattleScene* m_Scene;

    PentagramField m_currentField = PentagramField::Will;
    PentagramData_T m_currentData;

    std::vector<Button*> m_PentragramButtons;
    std::vector<Button*> m_IntButtons;
    std::vector<Button*> m_ArrowButtons;

    Button* m_InvokeButton;
    Button* m_PassButton;
public:
    PentragramController(BattleScene* scene);
    void SetPentagramField(PentagramField selectedField);
    void SetPentagramValue(int value);
    
    void SetInvokeButtonActive(bool isActive) { m_InvokeButton->SetActive(isActive); }

};