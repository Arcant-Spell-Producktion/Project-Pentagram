#pragma once
#include "SpellCaster.h"

class CasterController
{
public:
    SpellCaster* m_SpellCaster = nullptr;

    ~CasterController()
    {
        delete m_SpellCaster;
    }
};