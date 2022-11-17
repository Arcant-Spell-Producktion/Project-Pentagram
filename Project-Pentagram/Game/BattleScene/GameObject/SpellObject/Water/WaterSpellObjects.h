#pragma once
#include <Game/BattleScene/GameObject/SpellObject/BaseSpellObject.h>

class WaterSpell1 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WaterSpell1(CasterPosition target) :BaseSpellObject(
        target,
        "Fireball_Object",
        "Sprites/Spell/Water/spell_water_1.png")
    {
        std::cout << "Spell:: Create WaterBall\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell2 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WaterSpell2(CasterPosition target) :BaseSpellObject(
        target,
        "Firearrow_Object",
        "Sprites/Spell/Water/spell_water_2.png")
    {
        std::cout << "Spell:: Create Barrage\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell3: public BaseSpellObject
{
private:
    void Initialize();
public:
    WaterSpell3(CasterPosition target) :BaseSpellObject(
        target,
        "Firewall_Object",
        "Sprites/Spell/Water/spell_water_3.png")
    {
        std::cout << "Spell:: Create Dew\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell4 : public BaseSpellObject
{
private:
    float x_Positions[3] = { 500.0f, 0.0f, -500.0f };
    int x_index = 0;
    bool canMove = true;
    void Initialize();
public:
    WaterSpell4(CasterPosition target) :BaseSpellObject(
        target,
        "Firewall_Object",
        "Sprites/Spell/Water/spell_water_4.png")
    {
        std::cout << "Spell:: Create Rebound\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell5 : public BaseSpellObject
{
private:
    std::vector<GameObject*> m_objectList;

    float m_localTimer = 0.0f;
    const int m_SpawnCount = 10;
    int m_SnapCount = 10;
    int m_DoneCount = 0;
    void Initialize();
public:
    WaterSpell5(CasterPosition target) :BaseSpellObject(
        target,
        "Firesnap_Object",
        "Sprites/Spell/Water/spell_water_5.png")
    {
        std::cout << "Spell:: Create Calm\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell6 : public BaseSpellObject
{
private:
    std::vector<GameObject*> m_Section;
    void Initialize();
public:
    WaterSpell6(CasterPosition target) :BaseSpellObject(
        target,
        "Waterbeam_object",
        "Sprites/Spell/Water/spell_water_6.png")
    {
        std::cout << "Spell:: Create Beam\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell7 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WaterSpell7(CasterPosition target) :BaseSpellObject(
        target,
        "FireMeteor_Object",
        "Sprites/Spell/Water/spell_water_7.png")
    {
        std::cout << "Spell:: Create Meteor\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell8 : public BaseSpellObject
{
private:
    float lifeTime = 1.5f;
    float spawnTime = 0.2f;
    int amount = 20;

    void Initialize();
public:
    WaterSpell8(CasterPosition target) :BaseSpellObject(
        target,
        "FireDragon_Object",
        "Sprites/Spell/Water/spell_water_8-1.png")
    {
        std::cout << "Spell:: Create Dragon\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};

class WaterSpell9 : public BaseSpellObject
{
private:
    void Initialize();
public:
    WaterSpell9(CasterPosition target) :BaseSpellObject(
        target,
        "Hell_Object",
        "Sprites/Spell/Water/spell_water_9.png")
    {
        std::cout << "Spell:: Create Hell\n";
        Initialize();
        BaseSpellObject::Initialize();
    };
};


class WaterSpellObject
{
public:
    static BaseSpellObject* CreateSpellObject(int index, CasterPosition target);
};