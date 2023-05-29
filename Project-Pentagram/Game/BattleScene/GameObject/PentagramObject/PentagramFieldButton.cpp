#include "PentagramFieldButton.h"
#include "Engine/GameStateController.h"

const std::string PentagramFieldButtonPath = "Sprites/UI/Game/ui_game_pentagram-buttons.png";

void PentagramFieldButton::OnUpdate(const float& dt)
{
    float speed = 0.3f;
    for (auto rune : m_RuneList)
    {
        rune->Theta += speed * dt;
        rune->UpdateRadialPosition();
        SetRuneActive(m_ActiveRune);
    }
}

void PentagramFieldButton::SetElement(Element::Type element)
{
    m_CurrentElement = element;

    int fieldIndex = (int)m_SelectedField + 1;
    int elementIndex = (int)m_CurrentElement + 1;

    ElementSignature->SetSpriteByIndex(fieldIndex, elementIndex);

    if (m_SelectedField == PentagramField::Will)
    {
        std::string rune_text = "";

        switch (m_CurrentElement)
        {
        case Element::Earth:
            rune_text = "QUAKEX";
            break;
        case Element::Fire:
            rune_text = "BLAZES";
            break;
        case Element::Water:
            rune_text = "WATERZ";
            break;
        case Element::Wind:
            rune_text = "STORME";
            break;
        }

        for (int i = 0;i < 6; i++)
        {
            m_RuneList[i]->SetRune(rune_text[i]);
        }
    }
}

void PentagramFieldButton::SetActive(const bool& active)
{
    GameObject::SetActive(active);
    if(m_SelectedField != PentagramField::Complex) ComplexRune->SetActive(false);
}

void PentagramFieldButton::SetToggle(bool isToggle)
{
    if (isToggle)
    {
        m_buttonState = ButtonState::Down;
        ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
        this->SetSpriteByIndex(0, 1);
    }
    else
    {
        m_buttonState = ButtonState::Idle;
        ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
        this->SetSpriteByIndex(0, 0);
    }
}

void PentagramFieldButton::SetRuneActive(int amount)
{
    m_ActiveRune = amount;
    for (size_t i = 0; i < m_RuneList.size(); i++)
    {
        m_RuneList[i]->SetActive( i+1 <= m_ActiveRune);
    }
}

void PentagramFieldButton::SetRuneColor(glm::vec4 runeColor)
{
    for (size_t i = 0; i < m_RuneList.size(); i++)
    {
        m_RuneList[i]->color = runeColor;
    }
}

PentagramFieldButton::PentagramFieldButton(PentagramField field, Element::Type element) :Button("Pentagram_Button_"+ std::to_string((int)field)), m_SelectedField(field),m_CurrentElement(element)
{
   
    m_buttonState = ButtonState::Idle;

    this->onBeginHover = [this](Button* button)
    {
        if (m_buttonState == ButtonState::Idle)
        {
            AudioController::GetInstance().PlaySFX("Audio/SFX/UI/Game/sfx_ui_game_pentagramcrystal_button_hover.wav", 0.5f);
        }
    };

    this->onHover = [this](Button* button)
    {
        m_HoverText->SetActive(true);

        if (m_buttonState == ButtonState::Idle)
        {
            m_buttonState = ButtonState::Hover;
            ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
        }
    };

    this->unHover = [this](Button* button)
    {
        m_HoverText->SetActive(false);

        if (m_buttonState == ButtonState::Hover)
        {
            m_buttonState = ButtonState::Idle;
            ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
        }
    };

    auto GameObjManager = GameStateController::GetInstance().currentScene;

    int fieldIndex = (int)m_SelectedField + 1;
    int elementIndex = (int)m_CurrentElement + 1;

    float size = 85.0f;
    this->SetTexture(PentagramFieldButtonPath);
    this->scale = { size ,size , 1.0f };
    this->SetIsSlicing(false);
    this->SetIsAnimationObject(false);

    FieldSignature = new UIObject("FieldIcon");
    FieldSignature->SetTexture(PentagramFieldButtonPath);
    FieldSignature->scale = { size, size, 1.0f };
    FieldSignature->SetSpriteByIndex(fieldIndex, 0);
    FieldSignature->SetIsAnimationObject(false);

    ElementSignature = new UIObject("ElementIcon");
    ElementSignature->SetTexture(PentagramFieldButtonPath);
    ElementSignature->scale = { size , size, 1.0f };
    ElementSignature->SetIsAnimationObject(false);

    ButtonCover = new UIObject("ButtonCover");
    ButtonCover->SetTexture(PentagramFieldButtonPath);
    ButtonCover->scale = { size, size, 1.0f };
    ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
    ButtonCover->SetIsAnimationObject(false);

    ComplexRune = new RuneObject(0);
    ComplexRune->SetActive(false);
    ComplexRune->SetIsAnimationObject(true);
    ComplexRune->SetAnimationPlayTime(0.5f);

    m_HoverText = new TextObject("HoverText");
    m_HoverText->fontSize = 32;
    m_HoverText->outlineColor = AC_BLACK;
    m_HoverText->textAlignment = TextAlignment::MID;
    
    this->SetChildRenderFront(FieldSignature);
     
    this->SetChildRenderFront(ComplexRune);

    this->SetChildRenderFront(ButtonCover);

    this->SetChildRenderFront(ElementSignature);

    switch (m_SelectedField)
    {
    case PentagramField::Circle:
        m_RuneList = RuneObjectFactory::CreateRunes("NOARML");
        m_HoverText->text = "Circle";
        m_HoverText->position = {0.0f,60.0f,0.0f};
        break;
    case PentagramField::Complex:
        m_RuneList = RuneObjectFactory::CreateRunes("TUNERF");
        ComplexRune->SetActive(true);
        m_HoverText->text = "Complex";
        m_HoverText->position = { 0.0f, 60.0f,0.0f };

        break;
    case PentagramField::Will:
        m_RuneList = RuneObjectFactory::CreateRunes("VWXYZA");
        m_HoverText->text = "Will";
        m_HoverText->position = { -90.0f, 0.0f,0.0f };
        break;
    case PentagramField::Effect:
        m_RuneList = RuneObjectFactory::CreateRunes("AMOGUS");
        m_HoverText->text = "Effect";
        m_HoverText->position = { 110.0f, 0.0f,0.0f };

        break;
    case PentagramField::Time:
        m_RuneList = RuneObjectFactory::CreateRunes("DAPINGPREAWAMAMAYMON");
        m_HoverText->text = "Time";
        m_HoverText->position = { -90.0f, 0.0f,0.0f };
        break;
    }

    SetElement(m_CurrentElement);

    float radius = 50.0f;
    int rune_i = 0;
    for (auto rune : m_RuneList)
    {
        this->SetChildRenderFront(rune);
        rune->Radius = radius;
        rune->Theta = 2.0f * 3.142526 * rune_i / m_RuneList.size();
        rune->UpdateRadialPosition();
        rune_i++;
        rune->SetActive(false);
    }

    this->SetChildRenderFront(m_HoverText);
}
