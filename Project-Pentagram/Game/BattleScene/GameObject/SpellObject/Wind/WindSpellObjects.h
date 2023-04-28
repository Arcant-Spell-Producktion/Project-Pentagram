#pragma once
#include <Game/BattleScene/GameObject/SpellObject/BaseSpellObject.h>

class WindSpell1 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WindSpell1(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind1.png")
    {
        std::cout << "Spell:: Create WindBall\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};


class WindSpellObject
{
public:
    static BaseSpellObject* CreateSpellObject(int index, CasterPosition target);
};