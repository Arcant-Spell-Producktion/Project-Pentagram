#pragma once

#include "Engine/GameScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Utilities/Color.h"
#include "Game/Spells/Element.h"

class MapScene : public GameScene
{
private:
    UIObject* m_FadeScreen = nullptr;
    GameState m_NextState;
    float m_FadeTime;
    float m_FadeCurrentTime = 0.0f;
    bool m_IsFadeOut = false;

    float m_MoveTime = 1.0f;
    float m_CurrentMoveTime = 0.0f;
    GameObject* m_Character;
    glm::vec3 m_StartPoint;
    glm::vec3 m_Destination;
    bool m_MoveCharacter = false;

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