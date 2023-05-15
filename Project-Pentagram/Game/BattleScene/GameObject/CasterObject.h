#pragma once

#include <functional>

#include "EffectObject/BaseEffectObject.h"
#include "Engine/IGameObjectManager.h"
#include "Game/Spells/Element.h"
#include "Game/GameData/CasterData/CasterType.h"
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
    std::map<SpellEffectEnum, BaseEffectObject*> m_Effects;

    std::function<void()> m_atk_callback = nullptr;

    CasterObjectState m_State = CasterObjectState::Idle;
    CasterObjectState m_NextState = CasterObjectState::Idle;

    CasterType m_CasterType = CasterType::Player;
    Element::Type m_CasterElement = Element::Type::Earth;

    int m_ChannelCounter = 0;
    bool m_doLoop = false;

    glm::vec4 originColor;
    float m_FlashTimer = 0.0f;
    bool m_IsStartFlash = false;

public:
    CasterObject();

    void OnUpdate(const float& dt) override;

    void SetState(CasterObjectState state);

    void SetState(CasterObjectState state, CasterObjectState nextState);

    void SetCaster(CasterType type, Element::Type element);
    void SetCaster(CasterType type, Element::Type element, CasterPosition pos);

    void PlayChannelAnim(int ChannelCount = 0);

    void PlayAttackAnim(bool isChannelSpell,std::function<void()> callback);

    void PlayDiedAnim();

    void PlayRedFlash() { m_IsStartFlash = true; m_FlashTimer = 0.8f; }

    void PlayEffect(SpellEffectEnum effect);

    void StopEffect(SpellEffectEnum effect);

};