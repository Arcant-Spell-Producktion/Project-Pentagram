#pragma once
#include "BaseBattleState.h"
#include "Game/BattleScene/SpellDispather.h"

class ResolveBattleState : public BaseBattleState
{
private:
    enum class ResolveState
    {
        ResolveTrack,
        ResolveSpell,
        PlaySpell,
        Waiting,
    };
    
    SpellDispatcher m_Dispatcher;
    SpellController* m_CurrentSpellController;

    ResolveState m_State = ResolveState::ResolveTrack;
    SpellTimetrack* m_CurrentTrack = nullptr;
    CastSpellDetail* m_CurrentSpellDetail = nullptr;
    int m_TrackResolveIndex = 0;
    int m_SpellResolveIndex = 0;

    float m_Timer = 0.0f;

    void Step();
    void ResolveTrack();
    void ResolveSpell();
    void ResolveDamgeCalculation();
public:
    ResolveBattleState() :BaseBattleState(BattleState::ResolveState) {}
    virtual void OnBattleStateIn()override;
    virtual void OnBattleStateUpdate(float dt) override;
    virtual void OnBattleStateOut() override;

};
