#pragma once
template <class STATE>
class BaseGameState
{
public:
    virtual ~BaseGameState() = default;
    const STATE StateID;

    BaseGameState() :StateID(static_cast<STATE>(0)) {}
    BaseGameState(const STATE id) :StateID(id) {}
    virtual void OnBattleStateIn() = 0;
    virtual void OnBattleStateUpdate(float dt) = 0;
    virtual void OnBattleStateOut() = 0;
};