#include "GameOverUI.h"
#include "ScrollButton.h"

GameOverUI::GameOverUI():UIObject("GameOverUI")
{
    this->color.a = 0.0f;
    this->position.x = 400.0f;

    Header = new TextObject("EJECTED!");
    Header->textAlignment = TextAlignment::MID;
    Header->text = "SKILL ISSUE!";
    Header->fontSize = 128.0f;
    Header->position.y = 300.0f;
    Header->color = AC_WHITE;
    

    ButtonA = new ScrollButton("Return to\nMain menu");
    ButtonA->SetButtonScale({ 600.0f,200.0f,1.0f }, { 640.0f,200.0f,1.0f });
    ButtonA->textObject.isVCenterAlignment = true;
    ButtonA->textObject.fontSize = 56.0f;
    ButtonA->position.y = 40.0f;

    ButtonB = new ScrollButton("Quit");
    ButtonB->SetButtonScale({ 600.0f,200.0f,1.0f }, { 640.0f,200.0f,1.0f });
    ButtonB->textObject.isVCenterAlignment = true;
    ButtonB->textObject.fontSize = 56.0f;
    ButtonB->position.y = -260.0f;

    this->SetChildRenderFront(Header);
    this->SetChildRenderBack(ButtonA);
    this->SetChildRenderBack(ButtonB);

    GameObject::SetActive(false);
}
