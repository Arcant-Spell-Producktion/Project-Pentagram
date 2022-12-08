#pragma once
struct CasterStat
{
    int CurrentHealth;
    int MaxHealth;

    int CurrentMana;
    int MaxMana;

    CasterStat(int hp = 1,int mana = 1)
    {
        CurrentHealth = MaxHealth = hp;
        CurrentMana = MaxMana = mana;
    }

    CasterStat(const CasterStat &stat)
    {
        MaxHealth = stat.MaxHealth;
        MaxMana = stat.MaxMana;

        CurrentHealth = stat.CurrentHealth;
        CurrentMana = stat.CurrentMana;
    }
};