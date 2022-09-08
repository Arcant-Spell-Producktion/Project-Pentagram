#pragma once
#include <string>

class Element
{
private:
    static const std::string enum_string[];
public:
    enum Type
    {
        NULLTYPE = -1,
        Fire = 0,
        Water,
        Wind,
        Earth,
        Debug
    };
    static Element::Type GetEnum(std::string typeString) {
        for (int i = 0; i < 3; i++)
        {
            if (typeString.compare(enum_string[i])) return Element::Type(i);
        }
        return Element::Debug;
    }
    static std::string GetString(Element::Type type) { return enum_string[(int)type]; }
};
