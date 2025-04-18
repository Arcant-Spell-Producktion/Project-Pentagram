#include "Engine/IGameObjectManager.h"
#include "Engine/GameStateController.h"
#include "RuneObject.h"

int CharToIndex(char c)
{
    return std::tolower(c) - 'a';
}

void RuneObject::SetRune(char runeChar)
{
    SetRune(CharToIndex(runeChar));
}

void RuneObject::SetRune(int runeIndex)
{
    this->SetSpriteByIndex(0, runeIndex);
}

RuneObject::RuneObject(int runeIndex) :UIObject("RuneObj")
{
    float size = 25.0f;
    this->scale = { size, size ,1.0f };
    this->SetTexture("Sprites/UI/Game/ui_game_runes.png");
    this->SetIsAnimationObject(false);
    this->SetSpriteByIndex(0,runeIndex);
    this->color = { 0.0f, 0.0f, 0.0f, 1.0f };
}

std::vector<RuneObject*> RuneObjectFactory::CreateRunes(const std::string text)
{
    std::vector<RuneObject*> runeList;
    auto GameObjManager = GameStateController::GetInstance().currentScene;

    for (auto _char :text)
    {
        int index = CharToIndex(_char);
        runeList.push_back(new RuneObject(index));
    }
    return runeList;
}
