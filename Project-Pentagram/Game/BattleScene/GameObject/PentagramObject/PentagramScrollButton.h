#pragma once
#include "Engine/IGameObjectManager.h"
#include "Engine/Audio/AudioController.h"

class PentagramScrollButton : public Button
{
protected:
    enum class ButtonState
    {
        Idle = 0,
        Hover,
        Down
    };

    UIObject* m_ButtonIcon;

    ButtonState m_buttonState;

    void SetState(ButtonState state);
public:
    Event<int> OnButtonClicked;

    PentagramScrollButton(IGameObjectManager* scene);

    UIObject*& GetButtonIcon() { return m_ButtonIcon; }
};

class PentagramScrollNumberButton: public PentagramScrollButton
{
private:
public:
    void SetToggle(bool isToggle);

    PentagramScrollNumberButton(int value, IGameObjectManager* scene);
};

class PentagramScrollArrowButton : public PentagramScrollButton
{
private:
    float m_downTime = 0.15f;
    float m_curtime = 0.0f;
    virtual void OnUpdate(const float& dt) override;
public:
    PentagramScrollArrowButton(int value, IGameObjectManager* scene);
};