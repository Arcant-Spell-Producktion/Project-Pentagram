#pragma once
struct PentagramData_T
{
    int circle = 1;
    int complex = 1;
    int will = 1;
    int effect = 1;
    int time = 1;
};

enum class PentagramField
{
    Time = 0,
    Circle,
    Complex,
    Will,
    Effect,
};

struct PentagramEvent
{
    PentagramField Field;
    int Value;

    PentagramEvent(PentagramField _field, int _value) :
        Field(_field), Value(_value) {}
};