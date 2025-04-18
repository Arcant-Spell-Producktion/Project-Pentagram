#pragma once
#include <atomic>

enum class SpellObjectState
{
    Init = 0,
    Ready,
    Activate,
    WaitTrigger,
    Hit,
    Done
};

class SpellController
{ 
protected:
   SpellObjectState m_SpellState = SpellObjectState::Init;
public:
    bool Trigger = false;

    SpellObjectState GetSpellState() const { return m_SpellState; }
    bool IsSpellWaitTrigger() const { return m_SpellState == SpellObjectState::WaitTrigger; }
    bool IsSpellHit() { return m_SpellState == SpellObjectState::Hit; }
     bool IsSpellDone() { return m_SpellState == SpellObjectState::Done; }

    virtual void Activate() = 0;
};