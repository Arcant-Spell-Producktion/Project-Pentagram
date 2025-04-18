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
        std::cout << "Spell:: Create WindCutter\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell2 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WindSpell2(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind2.png")
    {
        std::cout << "Spell:: Create WindBall\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell3 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WindSpell3(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind3.png")
    {
        std::cout << "Spell:: Create WindBall\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell4 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WindSpell4(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind4.png")
    {
        std::cout << "Spell:: Create WindCutter\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell5 : public BaseSpellObject
{
private:
    ParticleSystem* m_LeafParticle = nullptr;
    void Initialize();
public:
    WindSpell5(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind5.png")
    {
        std::cout << "Spell:: Create WindCutter\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell6 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WindSpell6(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind6.png")
    {
        std::cout << "Spell:: Create WindCutter\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell7 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WindSpell7(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind7.png")
    {
        std::cout << "Spell:: Create WindCutter\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell8 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WindSpell8(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind8.png")
    {
        std::cout << "Spell:: Create WindCutter\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpell9 : public BaseSpellObject
{
private:
    ParticleSystem* m_LeafParticle = nullptr;
    ParticleSystem* m_WindParticle = nullptr;
    ParticleSystem* m_FireParticle = nullptr;
    ParticleSystem* m_WaterParticle = nullptr;
    void Initialize();
public:
    WindSpell9(CasterPosition target) :BaseSpellObject(
        target,
        "Windball_Object",
        "Sprites/Spell/Wind/spell_sprite_wind9.png")
    {
        std::cout << "Spell:: Create WindCutter\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WindSpellObject
{
public:
    static BaseSpellObject* CreateSpellObject(int index, CasterPosition target);
};