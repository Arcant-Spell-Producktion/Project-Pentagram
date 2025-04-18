#pragma once
#include <bitset>

class SpellResolveEffect
{
private:
    std::bitset<6> m_flags;

public:
    SpellResolveEffect(int value = 1)
    {
        m_flags = value;
    }

    void SetResolveFlags (int value)
    {
        m_flags = value;
    }

    bool DoDamage() const
    {
        return m_flags[0];
    }

    bool DoCancelDamage() const
    {
        return m_flags[1];
    }

    bool DoReflectDamage() const
    {
        return m_flags[2];
    }

    bool DoCancelSpell() const
    {
        return m_flags[3] || DoDelaySpell() || DoCancelTrack();
    }

    bool DoDelaySpell() const
    {
        return m_flags[4];
    }

    bool DoCancelTrack() const
    {
        return m_flags[5];
    }
};
