#pragma once
#include "Engine/IGameObjectManager.h"

class ManaRouletteNumberUI :public UIObject
{
private:
public:
    ManaRouletteNumberUI(int index):UIObject("ManaRouletteNumberUI_" + index)
    {
        this->SetTexture("Sprites/UI/Interactable/Button/ui_interactable_scroll_button-number.png");
        this->SetIsSlicing(false);
        this->SetSpriteByIndex(1, 0);
        this->scale = { 80.0f,80.0f,1.0f };
    }

    void SetNumberByValue(int n)
    {
        this->SetSpriteByIndex(1, n - 1);
    }

    void SetIsUsed(bool isUsed)
    {

        if (!isUsed)
            this->color = { 1.0f, 1.0f, 1.0f, 1.0f };
        else
            this->color = { .5f , .5f , .5f , 0.15f };
    }
};