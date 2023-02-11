#pragma once
#include <array>;

struct CasterStat
{
    int CurrentHealth;
    int MaxHealth;

    int CurrentMana;
    int CurrentManaWheel = 0;

    std::array<int, 6> ManaWheel;

    CasterStat(int hp = 1, std::array<int, 6> manaWheel = {1,1,1,1,1,1})
    {
        CurrentHealth = MaxHealth = hp;
        ManaWheel = manaWheel;

        CurrentMana = manaWheel[CurrentManaWheel];
    }

    CasterStat(const CasterStat &stat)
    {
        CurrentHealth = stat.CurrentHealth;
        MaxHealth = stat.MaxHealth;

        CurrentMana = stat.CurrentMana;
        CurrentManaWheel = stat.CurrentManaWheel;

        ManaWheel = stat.ManaWheel;
    }
};