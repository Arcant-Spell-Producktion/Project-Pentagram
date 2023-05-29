#pragma once
#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Utilities/Color.h"

#include "Game/Objects/OptionMenuObject.h"
#include "Game/Objects/ConfirmUI.h"
#include "Game/Slideshow/SlideObject.h"

class IntroCutScene : public GameScene
{
private:
    UIObject* m_FadeScreen = nullptr;
    GameState m_NextState;
    float m_FadeTime;
    float m_FadeCurrentTime = 0.0f;
    bool m_IsFadeOut = false;

    SlideObject * m_IntroSlide = nullptr;
    void FadeOut(const float& fadeTime, GameState nextState)
    {
        m_NextState = nextState;
        m_FadeTime = fadeTime;
        m_IsFadeOut = true;
        m_FadeScreen->SetActive(true);
        m_FadeScreen->SetBlockRaycast(true);
    }
    void FadeUpdate(const float& dt);

public:
    virtual void GameSceneLoad() override;
    virtual void GameSceneInit() override;
    virtual void GameSceneUpdate(float dt) override;
    virtual void GameSceneFree() override;
};

