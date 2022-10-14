#include "Engine/IGameObjectManager.h"
#include "Engine/GameStateController.h"
#include "RuneObject.h"

void RuneObject::SetRune(int runeIndex)
{
    this->SetSpriteByIndex(0, runeIndex);
}

RuneObject::RuneObject(int runeIndex) :UIObject("RuneObj")
{
    float size = 35.0f;
    this->scale = { size,size ,1.0f };
    this->SetTexture("Sprites/UI/Game/ui_game_runes.png");
    this->SetIsAnimationObject(false);
    this->SetSpriteByIndex(0,runeIndex);
    this->color = { 0.0f,1.0f, 0.0f, 1.0f };
}

std::vector<RuneObject*> RuneObjectFactory::CreateRunes(const std::string text)
{
    std::vector<RuneObject*> runeList;
    auto GameObjManager = GameStateController::GetInstance()->currentScene;

    for (auto _char :text)
    {
        int index = std::tolower(_char) - 'a';
        runeList.push_back(
            GameObjManager->CreateObject<RuneObject>(new RuneObject(index))
        );
    }
    return runeList;
}
