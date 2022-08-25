#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std;

class SideEffectType
{
private:
    static const const string enum_string[];
public:
    static enum Type
    {
        None = 0,
        Mark,
        Burn
    };
    static SideEffectType::Type GetEnum(string typeString) {
        for (int i = 0; i < 3; i++)
        {
            if (typeString.compare(enum_string[i])) return SideEffectType::Type(i);
        }
        return SideEffectType::None;
    }
};

class ChannelEffectType
{
private:
    static const const string enum_string[];
public:
    static enum Type
    {
        None = 0,
        Wait,
        Active
    };
    static ChannelEffectType::Type GetEnum(string typeString) {
        for (int i = 0; i < 3; i++)
        {
            if (typeString.compare(enum_string[i])) return ChannelEffectType::Type(i);
        }
        return ChannelEffectType::None;
    }
};

class Spell
{
private:
    std::string m_Name = "New Spell";
    int m_WillValues[6];
    SideEffectType::Type m_SideEffectType = SideEffectType::None;
    int m_SideEffectValues[6] = { 0,0,0,0,0,0 };
    int m_OriginalCastTime = 1;
    ChannelEffectType::Type m_ChannelEffectType = ChannelEffectType::None;
    int m_ChannelTime = 0;
public:

    Spell() :
        m_Name("New Spell"),
        m_WillValues{ 0,0,0,0,0,0 },
        m_SideEffectType(SideEffectType::None),
        m_SideEffectValues{ 0,0,0,0,0,0 },
        m_OriginalCastTime(1),
        m_ChannelEffectType(ChannelEffectType::None),
        m_ChannelTime(0)
    {}

    void SetSpellName(std::string name) { m_Name = name; }
    std::string GetSpellName() { return m_Name; }

    void SetWillValue(int i, int value) { m_WillValues[i] = value; }
    int GetWillValue(int i) { return m_WillValues[i]; }

    void SetSideEffectType(SideEffectType::Type type) { m_SideEffectType = type; }
    SideEffectType::Type GetSideEffectType() { return m_SideEffectType; }

    void SetSideEffectValue(int i, int value) { m_SideEffectValues[i] = value; }
    int GetSideEffectValue(int i) { return m_SideEffectValues[i]; }

    void SetCastTime(int time) { m_OriginalCastTime = time; }
    int GetCastTime() { return m_OriginalCastTime; }

    void SetChannelEffectType(ChannelEffectType::Type type) { m_ChannelEffectType = type; }
    ChannelEffectType::Type GetChannelEffectType() { return m_ChannelEffectType; }

    void SetChannelTime(int time) { m_ChannelTime = time; }
    int GetChannelTime() { return m_ChannelTime; }
};

