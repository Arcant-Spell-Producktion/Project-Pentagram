﻿#pragma once
#include "Game/BattleScene/BattleStates/BaseBattleState.h"
#include "Game/BattleScene/SpellDispather.h"

class ResolveTutorialState : public BaseBattleState
{
private:
    enum class ResolveState
    {
        ResolveTrack,
        PlayCompare,
        ResolveSpell,
        PlayTriggeredSpell,
        PlaySpell,
        Waiting,
    };
    

    SpellDispatcher m_Dispatcher;
    SpellController* m_CurrentSpellController;

    ResolveState m_State = ResolveState::ResolveTrack;
    SpellTimetrack* m_CurrentTrack = nullptr;
    std::vector<CastSpellDetail*> m_ResolveTrack;
    CastSpellDetail* m_CurrentSpellDetail = nullptr;
    int m_TrackResolveIndex = 0;
    int m_SpellResolveIndex = 0;

    float m_Timer = 0.0f;

    void Step();
    void ResolveTrack();
    void ResolveSpell(int spell_index = -1);
    void ResolveDamageCalculation();
public:
    ResolveTutorialState() :BaseBattleState(BattleState::ResolveState) {}
    virtual void OnBattleStateIn() override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;

};
