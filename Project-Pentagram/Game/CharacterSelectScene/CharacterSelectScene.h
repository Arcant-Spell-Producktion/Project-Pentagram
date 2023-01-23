#pragma once

#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Utilities/Color.h"
#include "Game/Spells/Element.h"

class CharacterSelectScene : public GameScene
{
private:
    UIObject* m_FadeScreen = nullptr;
    GameState m_NextState;
    float m_FadeTime;
    float m_FadeCurrentTime = 0.0f;
    bool m_IsFadeOut = false;

    Element::Type m_SelectedElement = Element::Fire;
    std::vector<UIObject*> m_Characters;

    void FadeOut(const float& fadeTime, GameState nextState)
    {
        m_NextState = nextState;
        m_FadeTime = fadeTime;
        m_IsFadeOut = true;
    }
    void FadeUpdate(const float& dt);


public:
    void OnSelect(Element::Type element);
    void OnConfirm();

    virtual void GameSceneLoad() override;
    virtual void GameSceneInit() override;
    virtual void GameSceneUpdate(float dt) override;
    virtual void GameSceneFree() override;
};