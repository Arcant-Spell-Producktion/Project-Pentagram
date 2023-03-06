#pragma once
#include <atomic>

enum class SpellObjectState
{
    Init = 0,
    Ready,
    Activate,
    Hit,
    Done
};

class SpellController
{ 
protected:
   SpellObjectState m_SpellState = SpellObjectState::Init;
public:
    SpellObjectState GetSpellState() const { return m_SpellState; }
    bool IsSpellHit() { return m_SpellState == SpellObjectState::Hit; }
     bool IsSpellDone() { return m_SpellState == SpellObjectState::Done; }

    virtual void Activate() = 0;
};