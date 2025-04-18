#include "Engine/IGameObjectManager.h"
#include <vector>

class RuneObject : public UIObject
{

public:
    float Theta = 0.0f;
    float Radius = 0.0f;

    void SetRune(char runeChar);
    void SetRune(int runeIndex);
    RuneObject(int runeIndex);

    void UpdateRadialPosition()
    {
        this->position = { Radius * sinf(Theta),Radius * cosf(Theta) ,0.0f };
    }
};

class RuneObjectFactory
{
public:
    static std::vector<RuneObject*> CreateRunes(const std::string text);
};