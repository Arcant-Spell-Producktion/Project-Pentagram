#pragma once
#include "PentagramFieldButton.h"

class PentagramFieldButtonUI: public UIObject
{
private:
    std::vector<PentagramFieldButton*> m_PentragramButtons;

    int GetIndexByField(PentagramField field);

    void ToggleButton(PentagramField button_field);

    PentagramField GetFieldByIndex(int index);
public:
    Event<PentagramField> OnFieldButtonClicked;

    void SetFieldButtonRune(PentagramField field, int n);

    void ResetFieldRune();

    PentagramFieldButtonUI(IGameObjectManager* scene);
};