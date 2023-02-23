#include "PentagramScrollButtonManagerUI.h"

const std::string ButtonTexturePath = "Sprites/Button_Test.png";

void PentagramScrollButtonManagerUI::SetToggle(int index)
{
    if (m_CurrentField == PentagramField::Time)
    {
        //TODO::
    }
    else 
    {
        index -= 1;
        for (size_t i = 0; i < 6; i++)
        {
            m_IntButtons[i]->SetToggle(i == index);
            if(i != index) 
            { 
                m_IntButtons[i]->color = { 0.0f, 0.0f, 0.0f, 1.0f }; 
                m_IntButtons[i]->GetButtonIcon()->color = { 0.0f, 0.0f, 0.0f, 1.0f };
            }
            else 
            { 
                m_IntButtons[i]->color = { 1.0f, 1.0f, 0.0f, 1.0f };
                m_IntButtons[i]->GetButtonIcon()->color = { 1.0f, 1.0f, 0.0f, 1.0f };
            }
        }
    }
}

void PentagramScrollButtonManagerUI::SetScrollMode(PentagramField field)
{
    m_CurrentField = field;
    switch (m_CurrentField)
    {
    case PentagramField::Circle:
    case PentagramField::Complex:
        for (size_t i = 0; i < 6; i++)
        {
            if (i > 2)
            {
                m_IntButtons[i]->SetActive(false);
                continue;
            }
            m_IntButtons[i]->SetActive(true);
            m_IntButtons[i]->position.x = -240.0f + ((i + 1) * 120.0f);
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(false);
        }
        m_Scroll->scale = { 420.0f, 160.0f,0.0f };
        break;
    case PentagramField::Will:
    case PentagramField::Effect:
        for (size_t i = 0; i < 6; i++)
        {
            m_IntButtons[i]->SetActive(true);
            m_IntButtons[i]->position.x = -420.0f + ((i + 1) * 120.0f);
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(false);
        }
        m_Scroll->scale = { 800.0f, 160.0f,0.0f };
        break;
    case PentagramField::Time:
        for (size_t i = 0; i < 6; i++)
        {
            m_IntButtons[i]->SetActive(false);
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(true);
        }
        m_Scroll->scale = { 400.0f, 160.0f,0.0f };
        break;
    }
}

void PentagramScrollButtonManagerUI::SetScrollMode(PentagramEvent e)
{
    SetScrollMode(e.Field);
    SetToggle(e.Value);
}

PentagramScrollButtonManagerUI::PentagramScrollButtonManagerUI(IGameObjectManager* scene): UIObject("PentagramScrollButtons")
{
    this->color.a = 0.0f;

    m_Scroll = new UIObject("Scroll_1");
    m_Scroll->SetIsSlicing(true);
    m_Scroll->SetTexture("Sprites/UI/Game/ui_game_scroll.png");
    m_Scroll->SetSlicingBorderSize(200.0f);
    m_Scroll->SetSlicingBorderMultiplier(0.25f);
    m_Scroll->SetSlicingType(SlicingType::REPEAT);
    m_Scroll->position = { 0.0f, -250.0f, 0.0f };
    m_Scroll->scale = { 800.0f, 160.0f, 0.0f };
    this->SetChildRenderBack(m_Scroll);

    for (size_t i = 1; i <= 6; i++)
    {
        PentagramScrollNumberButton* button = (new PentagramScrollNumberButton(i,scene));
        button->position = { -420.0f + (i * 120.0f), 0.0f ,0.0f };
        
        button->OnButtonClicked += [this](int value)
        {
            this->OnScrollButtonClicked.Invoke(value);
            this->SetToggle(value);
        };

        m_IntButtons.push_back(button);
        m_Scroll->SetChildRenderFront(button);
    }

    for (size_t i = 0; i < 2; i++)
    {
        int value = i == 0 ? -1 : 1;
        PentagramScrollArrowButton* button = new PentagramScrollArrowButton(value, scene);
        button->position = { -80.0f + (i * 160.0f), 0.0f, 0.0f };

        button->OnButtonClicked += [this](int value)
        {
            this->OnScrollButtonClicked.Invoke(value);
        };

        m_ArrowButtons.push_back(button);
        m_Scroll->SetChildRenderFront(button);
        button->SetActive(false);
    }

    SetScrollMode({ PentagramField::Time , 0});
}
