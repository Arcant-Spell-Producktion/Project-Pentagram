#pragma once
#include <vector>
#include "Engine/GameScene.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"

class PentragramController: public GameObject
{
private:
    GameScene* m_Scene;

    PentagramField m_currentField = PentagramField::Will;
    PentagramData_T m_currentData;

    std::vector<GameObject*> m_PentragramObj;
    std::vector<Button*> m_PentragramButtons;
    std::vector<Button*> m_IntButtons;
    std::vector<Button*> m_ArrowButtons;

    Button* m_InvokeButton;
    Button* m_PassButton;

    UIObject* m_Scroll_1;
    UIObject* m_Scroll_2;
public:
    PentragramController();

    virtual void OnUpdate(const float& dt) override;

    void SetPentagramField(PentagramField selectedField);
    void SetPentagramValue(int value);
    
    void SetInvokeButtonActive(bool isActive) { m_InvokeButton->SetActive(isActive); }

    PentagramData_T ResetPentagram();

};