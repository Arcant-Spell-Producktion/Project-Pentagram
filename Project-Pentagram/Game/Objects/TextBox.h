#pragma once
#include "Engine/IGameObjectManager.h"
class TextBox : public Button
{
private:

    int direction = 1;
    float m_ClickY = 0.0f;
    UIObject* m_Click;

public:
    TextBox(std::string text);

    void OnUpdate(const float& dt) override;
};