#pragma once
#include "PentagramFieldButton.h"
#include "Engine/Audio/AudioController.h"

class PentagramFieldButtonUI: public UIObject
{
private:
    std::vector<PentagramFieldButton*> m_PentragramButtons;

    int GetIndexByField(PentagramField field);

    PentagramField GetFieldByIndex(int index);
public:
    Event<PentagramField> OnFieldButtonClicked;

    void ToggleButton(PentagramField button_field);

    void SetFieldButtonRune(PentagramField field, int n);

    void ResetFieldRune();

    void SetFieldButtonActive(PentagramField field, bool active);

    PentagramFieldButton* GetButtonByField(PentagramField field);

    PentagramFieldButtonUI(IGameObjectManager* scene);
};