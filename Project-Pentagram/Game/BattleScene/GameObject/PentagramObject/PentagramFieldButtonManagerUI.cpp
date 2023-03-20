#include "PentagramFieldButtonManagerUI.h"

int PentagramFieldButtonUI::GetIndexByField(PentagramField field)
{
    int index_value = -1;

    switch (field)
    {
    case PentagramField::Time:
        index_value = 0;
        break;
    case PentagramField::Complex:
        index_value = 1;
        break;
    case PentagramField::Effect:
        index_value = 2;
        break;
    case PentagramField::Will:
        index_value = 3;
        break;
    case PentagramField::Circle:
        index_value = 4;
        break;
    }

    return index_value;
}

void PentagramFieldButtonUI::ToggleButton(PentagramField button_field)
{
    for (size_t i = 0; i < 5; i++)
    {
        if (GetFieldByIndex(i) == button_field)
        {
            m_PentragramButtons[i]->SetRuneColor({ 1.0f, 1.0f, 0.0f, 1.0f });
        }
        else
        {
            m_PentragramButtons[i]->SetRuneColor({ 0.0f, 0.0f, 0.0f, 1.0f });
        }
        m_PentragramButtons[i]->SetToggle(GetFieldByIndex(i) == button_field);
    }
}

PentagramField PentagramFieldButtonUI::GetFieldByIndex(int index)
{
    PentagramField field_value;

    switch (index)
    {
    case 0:
        field_value = PentagramField::Time;
        break;
    case 1:
        field_value = PentagramField::Complex;
        break;
    case 2:
        field_value = PentagramField::Effect;
        break;
    case 3:
        field_value = PentagramField::Will;
        break;
    case 4:
        field_value = PentagramField::Circle;
        break;
    }

    return field_value;
}

void PentagramFieldButtonUI::SetFieldButtonRune(PentagramField field, int n)
{
    m_PentragramButtons[GetIndexByField(field)]->SetRuneActive(n);
}

void PentagramFieldButtonUI::ResetFieldRune()
{
    for (size_t i = 0; i < 5; i++)
    {
        m_PentragramButtons[i]->SetRuneActive(GetFieldByIndex(i) == PentagramField::Time ? 0 : 1);
    }
}

PentagramFieldButtonUI::PentagramFieldButtonUI(IGameObjectManager* scene): UIObject("PentagramFieldButtons")
{
    this->color.a = 0.0f;

    for (size_t i = 0; i < 5; i++)
    {
        float theta = 2.0f * 3.142526f * (i / 5.0f);
        float radius = 185.0f;

        PentagramField field_value = GetFieldByIndex(i);

        PentagramFieldButton* button = new PentagramFieldButton(field_value, Element::Fire);
        button->onClick = [this, field_value](Button* _button)
        {
            PentagramFieldButton* pentagramButton = dynamic_cast<PentagramFieldButton*>(_button);
            if (pentagramButton->GetButtonState() == PentagramFieldButton::ButtonState::Hover)
            {
                AudioController::GetInstance()->StopSFXLoop("Audio/SFX/UI/Game/sfx_ui_game_pentagramcrystal_button_hover_loop.wav");
                AudioController::GetInstance()->PlaySFX("Audio/SFX/UI/Game/sfx_ui_game_pentagramcrystal_button_press.wav", 1.0f);
            }
            ToggleButton(field_value);
            OnFieldButtonClicked.Invoke(field_value);
        };

        button->position = { radius * sinf(theta),radius * cosf(theta),0.0f };
         
        m_PentragramButtons.push_back(button);
        this->SetChildRenderFront(button);
    }
}
