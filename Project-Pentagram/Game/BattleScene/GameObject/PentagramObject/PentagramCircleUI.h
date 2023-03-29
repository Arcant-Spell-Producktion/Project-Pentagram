#pragma once
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"

#define PENTAGRAM_CIRCLE_OFFSET_Y 50.0f

class PentagramCircleUI : public UIObject
{
private:
    std::vector<UIObject*> m_PentragramObj;

    int m_ComplexValue = 1;
    int m_CircleValue = 1;

    void SetComplex(int value);
    void SetCircle(int value);

    virtual void OnUpdate(const float& dt) override;

public:
    PentagramCircleUI(IGameObjectManager* scene);

    void SetPentagramUI(int circle, int complex);

    void UpdateCircleUI(PentagramEvent e);

    int GetComplexValue();
    int GetCircleValue();
};
