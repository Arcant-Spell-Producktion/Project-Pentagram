#pragma once
#include <Game/BattleScene/GameObject/SpellObject/BaseSpellObject.h>

class EarthSpell1 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell1(CasterPosition target) :BaseSpellObject(
        target,
        "Fireball_Object",
        "Sprites/Spell/Earth/spell_earth_1.png")
    {
        std::cout << "Spell:: Create Fireball\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class EarthSpellObject
{
public:
    static BaseSpellObject* CreateSpellObject(int index, CasterPosition target);
};