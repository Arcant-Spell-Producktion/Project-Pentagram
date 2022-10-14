#include "PentagramFieldButton.h"
#include "Engine/GameStateController.h"

const std::string PentagramFieldButtonPath = "Sprites/UI/Game/ui_game_pentagram-buttons.png";

PentagramFieldButton::PentagramFieldButton(PentagramField field, Element::Type element) :Button("Pentagram_Button_"+ (int)field), m_SelectedField(field),m_CurrentElement(element)
{

    auto GameObjManager = GameStateController::GetInstance()->currentScene;

    int fieldIndex = (int)m_SelectedField + 1;
    int elementIndex = (int)m_CurrentElement + 1;

    float size = 120.0f;
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
    ElementSignature->SetSpriteByIndex(fieldIndex, elementIndex);
    ElementSignature->SetIsAnimationObject(false);

    ButtonCover = GameObjManager->CreateUIObject("ButtonCover");
    ButtonCover->SetTexture(PentagramFieldButtonPath);
    ButtonCover->scale = { size ,size , 1.0f };
    ButtonCover->SetSpriteByIndex(0, (int)ButtonState::Idle);
    ButtonCover->SetIsAnimationObject(false);

    this->SetChildRenderFront(FieldSignature);
     
    this->SetChildRenderFront(ElementSignature);
    
    this->SetChildRenderFront(ButtonCover);
}
