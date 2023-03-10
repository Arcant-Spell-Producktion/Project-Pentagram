#pragma once
#include <Game/BattleScene/GameObject/SpellObject/BaseSpellObject.h>

class EarthSpell1 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell1(CasterPosition target) :BaseSpellObject(
        target,
        "RockBullet_Object",
        "Sprites/Spell/Earth/spell_earth_1.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell2 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell2(CasterPosition target) :BaseSpellObject(
        target,
        "RockWave_Object",
        "Sprites/Spell/Earth/spell_earth_2.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell3 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell3(CasterPosition target) :BaseSpellObject(
        target,
        "RisingPillar_Object",
        "Sprites/Spell/Earth/spell_earth_3.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell4 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell4(CasterPosition target) :BaseSpellObject(
        target,
        "StoneLance_Object",
        "Sprites/Spell/Earth/spell_earth_4.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell5 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell5(CasterPosition target) :BaseSpellObject(
        target,
        "Fortified_Object",
        "Sprites/Spell/Earth/spell_earth_5.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell6 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell6(CasterPosition target) :BaseSpellObject(
        target,
        "EarthPrison_Object",
        "Sprites/Spell/Earth/spell_earth_6.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell7 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell7(CasterPosition target) :BaseSpellObject(
        target,
        "ReflectShield_Object",
        "Sprites/Spell/Earth/spell_earth_7.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell8 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell8(CasterPosition target) :BaseSpellObject(
        target,
        "UnbreakableShield_Object",
        "Sprites/Spell/Earth/spell_earth_8.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};

class EarthSpell9 : public BaseSpellObject
{
private:
    void Initialize();
public:
    EarthSpell9(CasterPosition target) :BaseSpellObject(
        target,
        "EarthDragon_Object",
        "Sprites/Spell/Earth/spell_earth_9.png")
    {
        Initialize();
        BaseSpellObject::Initialize();
    }
};


class EarthSpellObject
{
public:
    static BaseSpellObject* CreateSpellObject(int index, CasterPosition target);
};