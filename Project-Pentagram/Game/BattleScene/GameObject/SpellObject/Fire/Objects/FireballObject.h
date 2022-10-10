#pragma once
#include <Game/BattleScene/GameObject/SpellObject/BaseSpellObject.h>

class FireballObject : public BaseSpellObject
{
private:
    void Initialize();
public:
    FireballObject(CasterPosition target) :BaseSpellObject(
        target,
        "Fireball_Object",
        "Sprites/Spell/Fire/spell_fire_1.png") 
    {
        std::cout << "Spell:: Create Fireball\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};