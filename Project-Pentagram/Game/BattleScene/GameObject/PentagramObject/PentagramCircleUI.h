#pragma once
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/BattleScene/SpellCaster/PentagramData.h"

class PentagramCircleUI : public UIObject
{
private:
    std::vector<UIObject*> m_PentragramObj;

    void SetComplex(int value);
    void SetCircle(int value);

    virtual void OnUpdate(const float& dt) override;

public:
    PentagramCircleUI(IGameObjectManager* scene);

    void SetPentagramUI(int circle, int complex);

    void UpdateCircleUI(PentagramEvent e);
};
