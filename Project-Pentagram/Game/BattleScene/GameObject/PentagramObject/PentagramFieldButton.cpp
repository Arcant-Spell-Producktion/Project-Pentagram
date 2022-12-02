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

PentagramFieldButton::PentagramFieldButton(PentagramField field, Element::Type element) :Button("Pentagram_Button_"+ (int)field), m_SelectedField(field),m_CurrentElement(element)
{
   
    m_buttonState = ButtonState::Idle;

    this->onHover = [this](Button* button)
    {
        if (m_buttonState == ButtonState::Idle)
        {
            m_buttonState = ButtonState::Hover;
            ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
        }
    };

    this->unHover = [this](Button* button)
    {
        if (m_buttonState == ButtonState::Hover)
        {
            m_buttonState = ButtonState::Idle;
            ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
        }
    };

    auto GameObjManager = GameStateController::GetInstance()->currentScene;

    int fieldIndex = (int)m_SelectedField + 1;
    int elementIndex = (int)m_CurrentElement + 1;

    float size = 100.0f;
    this->SetTexture(PentagramFieldButtonPath);
    this->scale = { size ,size , 1.0f };
    this->SetIsSlicing(false);
    this->SetIsAnimationObject(false);

    FieldSignature = GameObjManager->CreateUIObject("FieldIcon");
    FieldSignature->SetTexture(PentagramFieldButtonPath);
    FieldSignature->scale = { size ,size , 1.0f };
    FieldSignature->SetSpriteByIndex(fieldIndex, 0);
    FieldSignature->SetIsAnimationObject(false);

    ElementSignature = GameObjManager->CreateUIObject("ElementIcon");
    ElementSignature->SetTexture(PentagramFieldButtonPath);
    ElementSignature->scale = { size ,size , 1.0f };
    ElementSignature->SetIsAnimationObject(false);

    ButtonCover = GameObjManager->CreateUIObject("ButtonCover");
    ButtonCover->SetTexture(PentagramFieldButtonPath);
    ButtonCover->scale = { size ,size , 1.0f };
    ButtonCover->SetSpriteByIndex(0, (int)m_buttonState);
    ButtonCover->SetIsAnimationObject(false);

    ComplexRune = GameObjManager->CreateObject<RuneObject>(new RuneObject(0));
    ComplexRune->SetActive(false);
    ComplexRune->SetIsAnimationObject(true);
    ComplexRune->SetAnimationPlayTime(0.5f);

    this->SetChildRenderFront(FieldSignature);
     
    this->SetChildRenderFront(ComplexRune);

    this->SetChildRenderFront(ButtonCover);

    this->SetChildRenderFront(ElementSignature);

    switch (m_SelectedField)
    {
    case PentagramField::Circle:
        m_RuneList = RuneObjectFactory::CreateRunes("ARM");

        break;
    case PentagramField::Complex:
        m_RuneList = RuneObjectFactory::CreateRunes("TUN");
        ComplexRune->SetActive(true);

        break;
    case PentagramField::Will:
        m_RuneList = RuneObjectFactory::CreateRunes("ABCDEF");
        break;
    case PentagramField::Effect:
        m_RuneList = RuneObjectFactory::CreateRunes("AMOGUS");

        break;
    case PentagramField::Time:
        m_RuneList = RuneObjectFactory::CreateRunes("DAPINGPREAWAMAMAYMON");

        break;
    }

    SetElement(m_CurrentElement);

    float radius = 60.0f;
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
}
