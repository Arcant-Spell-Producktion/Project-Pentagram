#pragma once
#include "BaseBattleState.h"

class ResolveBattleState : public BaseBattleState
{
private:
    enum class ResolveState
    {
        ResolveTrack,
        ResolveSpell,
        Waiting,
    };
    

    ResolveState m_State = ResolveState::ResolveTrack;
    SpellTimetrack* m_CurrentTrack = nullptr;
    int m_TrackResolveIndex = 0;
    int m_SpellResolveIndex = 0;

    float m_Timer = 0.0f;

    void Step();
    void ResolveTrack();
    void ResolveSpell();
public:
    ResolveBattleState() :BaseBattleState(BattleState::ResolveState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;

};
