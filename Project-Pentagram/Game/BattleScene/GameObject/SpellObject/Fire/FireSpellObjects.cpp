#include "FireSpellObjects.h"

BaseSpellObject* FireSpellObject::CreateSpellObject(int index, CasterPosition target)
{
    BaseSpellObject* object = nullptr;
    switch (index - 1)
    {
    case 0:
        object = new FireballObject(target);
    default:
        break;
    }
    return object;
}
