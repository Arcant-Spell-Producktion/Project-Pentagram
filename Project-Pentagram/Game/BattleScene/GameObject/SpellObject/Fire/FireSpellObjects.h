#pragma once
#include"Objects/FireballObject.h"

class FireSpellObject
{
public:
    static BaseSpellObject* CreateSpellObject(int index, CasterPosition target);
};