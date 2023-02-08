#include "PentagramScrollButton.h"

std::string ScrollButtonTexturePath = "Sprites/UI/Interactable/Button/";

void PentagramScrollButton::SetState(ButtonState state)
{
    m_buttonState = state;
    this->SetSpriteByIndex(0, (int)m_buttonState);
}

PentagramScrollButton::PentagramScrollButton(IGameObjectManager* scene) :Button("PentagramScrollButton")
{
    this->textObject.SetActive(false);

    m_buttonState = ButtonState::Idle;

    this->onHover = [this](Button* button)
    {
        if (m_buttonState == ButtonState::Idle)
        {
            SetState(ButtonState::Hover);
        }
    };

    this->unHover = [this](Button* button)
    {
        if (m_buttonState == ButtonState::Hover)
        {
            SetState(ButtonState::Idle);
        }
    };

    m_ButtonIcon = new UIObject("Button_Icon");

    this->SetChildRenderFront(m_ButtonIcon);
}

void PentagramScrollNumberButton::SetToggle(bool isToggle)
{
    if (isToggle)
    {
        SetState(ButtonState::Down);
    }
    else
    {
        SetState(ButtonState::Idle);
    }
}

PentagramScrollNumberButton::PentagramScrollNumberButton(int value, IGameObjectManager* scene) : PentagramScrollButton(scene)
{
    std::string randomTrackSFX = "Audio/SFX/UI/Game/sfx_ui_game_scroll_button_press_variant_" + std::to_string((rand() % 3) + 1) + ".wav";

    this->onClick = [this, randomTrackSFX, value](Button* button)
    {
        if (m_buttonState == ButtonState::Hover)
        {
            AudioController::GetInstance()->PlaySFX(randomTrackSFX, 1.0f);
            OnButtonClicked.Invoke(value);
        }
    };

    this->scale = { 80.0f, 80.0f, 1.0f };
    this->SetIsSlicing(false);
    this->textObject.SetActive(false);
    this->SetTexture(ScrollButtonTexturePath + "ui_interactable_scroll_button-number.png");
    this->SetSpriteByIndex(0, (int)m_buttonState);

    m_ButtonIcon->scale = { 80.0f, 80.0f, 1.0f };
    m_ButtonIcon->SetIsSlicing(false);
    m_ButtonIcon->SetTexture(ScrollButtonTexturePath + "ui_interactable_scroll_button-number.png");
    m_ButtonIcon->SetSpriteByIndex(1, value - 1);
}

void PentagramScrollArrowButton::OnUpdate(const float& dt)
{
    if (m_buttonState == ButtonState::Down)
    {
        m_curtime += dt;
        if (m_curtime >= m_downTime)
        {
            SetState(ButtonState::Idle);
        }
    }
}

PentagramScrollArrowButton::PentagramScrollArrowButton(int value, IGameObjectManager* scene) : PentagramScrollButton(scene)
{
    this->onClick = [this, value](Button* button)
    {
        AudioController::GetInstance()->PlaySFX("Audio/SFX/UI/Game/sfx_ui_game_timeline_button_press.wav", 0.75f);
        m_curtime = 0;
        SetState(ButtonState::Down);
        OnButtonClicked.Invoke(value);
    };

    this->scale = { 120.0f, 80.0f, 1.0f };
    this->SetIsSlicing(false);
    this->textObject.SetActive(false);
    this->SetTexture(ScrollButtonTexturePath + "ui_interactable_scroll_button-arrow.png");
    this->SetSpriteByIndex(0, (int)m_buttonState);

    m_ButtonIcon->scale = { 120.0f * value, 80.0f, 1.0f };
    m_ButtonIcon->SetIsSlicing(false);
    m_ButtonIcon->SetTexture(ScrollButtonTexturePath + "ui_interactable_scroll_button-arrow.png");
    m_ButtonIcon->SetSpriteByIndex(1, 0);
}
