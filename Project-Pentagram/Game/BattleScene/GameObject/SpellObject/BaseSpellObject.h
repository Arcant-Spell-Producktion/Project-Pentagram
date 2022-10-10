#pragma once
#include <Game/BattleScene/GameObject/SpellObject/SpellController.h>
#include <Game/GameData/CasterData/CasterPosition.h>
#include "Engine/GameScene.h"

#include <queue>
#include <functional>


class BaseSpellObject :public GameObject, public SpellController
{
private:
    typedef std::function<void(float)> SpellUpdateFunc;
    SpellUpdateFunc  m_CurrentUpdateFunc = nullptr;
    std::queue<SpellUpdateFunc> m_SpellUpdateQueue;
protected:
    int m_SpellTarget = 1;
    float m_TotalTime = 0.0f;

    void Next();

    void OnUpdate(const float& dt) override;

    void QueueUpdateFunction(SpellUpdateFunc func);

    void QueueHitEvent()
    {
        QueueUpdateFunction([this](float dt)
            { 
                std::cout << "\tSpell::Hit\n";
                m_SpellState = SpellObjectState::Hit;
                Next();
            });
    }

    void QueueDoneEvent()
    {
        QueueUpdateFunction([this](float dt)
            { 
                std::cout << "\tSpell::Done\n";
                m_SpellState = SpellObjectState::Done;
                Next();
            });
    }

    void Initialize();
public:
    BaseSpellObject(CasterPosition target, std::string spellName, std::string spellTexturePath);

    void Activate() override
    {
        while (m_SpellState != SpellObjectState::Ready) continue;
        m_TotalTime = 0.0f;
        m_SpellState = SpellObjectState::Activate;
    }
};