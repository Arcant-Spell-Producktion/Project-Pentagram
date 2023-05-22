#pragma once
#include "ScrollButton.h"
#include "Engine/IGameObjectManager.h"
class GameOverUI : public UIObject
{

public:
    TextObject* Header = nullptr;
    ScrollButton* ButtonA = nullptr;
    ScrollButton* ButtonB = nullptr;

    GameOverUI();
};