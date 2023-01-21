#pragma once

#include <functional>
#include "Engine/IGameObjectManager.h"
#include "Game/Spells/Element.h"
#include "Game/GameData/CasterData/CasterPosition.h"

enum class CasterObjectType
{
    Boss = 0,
    Minion = 1,
    Player = 2
};

enum class CasterObjectState
{
    Idle = 0,
    Cast,
    Attack,
    Die
};

class CasterObject : public GameObject
{
private:
    std::function<void()> m_atk_callback = nullptr;

    CasterObjectState m_State = CasterObjectState::Idle;
    CasterObjectState m_NextState = CasterObjectState::Idle;

    int m_ChannelCounter = 0;
    bool m_doLoop = false;

    float m_FlashTimer = 0.0f;

public:
    CasterObject();

    void OnUpdate(const float& dt) override;

    void SetState(CasterObjectState state);

    void SetState(CasterObjectState state, CasterObjectState nextState);

    void SetCaster(CasterObjectType type, Element::Type element, CasterPosition pos);

    void PlayChannelAnim(int ChannelCount = 0);

    void PlayAttackAnim(bool isChannelSpell,std::function<void()> callback);

    void PlayDiedAnim();

    void PlayRedFlash() { m_FlashTimer = 0.8f; }

};