#pragma once
#include <Game/BattleScene/GameObject/SpellObject/BaseSpellObject.h>

class FireSpell1 : public BaseSpellObject
{
private:
    void Initialize();
public:
    FireSpell1(CasterPosition target) :BaseSpellObject(
        target,
        "Fireball_Object",
        "Sprites/Spell/Fire/spell_fire_1.png")
    {
        std::cout << "Spell:: Create Fireball\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class FireSpell2 : public BaseSpellObject
{
private:
    void Initialize();
public:
    FireSpell2(CasterPosition target) :BaseSpellObject(
        target,
        "Firearrow_Object",
        "Sprites/Spell/Fire/spell_fire_2.png")
    {
        std::cout << "Spell:: Create FireArrow\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class FireSpell3: public BaseSpellObject
{
private:
    float lifeTime = 1.5f;
    float spawnTime = 0.2f;
    int amount = 20;

    void Initialize();
public:
    FireSpell3(CasterPosition target) :BaseSpellObject(
        target,
        "Firewall_Object",
        "Sprites/Spell/Fire/spell_fire_3.png")
    {
        std::cout << "Spell:: Create Firestorm\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class FireSpell4 : public BaseSpellObject
{
private:
    float localTimer = 0.0f;
    void Initialize();
public:
    FireSpell4(CasterPosition target) :BaseSpellObject(
        target,
        "Firewall_Object",
        "Sprites/Spell/Fire/spell_fire_4.png")
    {
        std::cout << "Spell:: Create Firewall\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class FireSpell5 : public BaseSpellObject
{
private:
    std::vector<GameObject*> m_objectList;

    float m_localTimer = 0.0f;
    const int m_SpawnCount = 10;
    int m_SnapCount = 10;
    int m_DoneCount = 0;
    void Initialize();
public:
    FireSpell5(CasterPosition target) :BaseSpellObject(
        target,
        "Firesnap_Object",
        "Sprites/Spell/Fire/spell_fire_5.png")
    {
        std::cout << "Spell:: Create Firesnap\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class FireSpell6 : public BaseSpellObject
{
private:
    void Initialize();
public:
    FireSpell6(CasterPosition target) :BaseSpellObject(
        target,
        "Firestorm_Object",
        "Sprites/Spell/Fire/spell_fire_6.png")
    {
        std::cout << "Spell:: Create Firewall\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class FireSpell7 : public BaseSpellObject
{
private:
    void Initialize();
public:
    FireSpell7(CasterPosition target) :BaseSpellObject(
        target,
        "FireMeteor_Object",
        "Sprites/Spell/Fire/spell_fire_7.png")
    {
        std::cout << "Spell:: Create Meteor\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};


class FireSpellObject
{
public:
    static BaseSpellObject* CreateSpellObject(int index, CasterPosition target);
};