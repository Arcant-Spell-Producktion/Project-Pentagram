#pragma once
#include <Game/BattleScene/GameObject/SpellObject/SpellController.h>
#include <Game/GameData/CasterData/CasterPosition.h>
#include "Engine/IGameObjectManager.h"
#include "Engine/Audio/AudioController.h"

#include <queue>
#include <functional>

class BaseSpellObject :public GameObject, public SpellController
{
private:
    typedef std::function<void(float)> SpellUpdateFunc;
    SpellUpdateFunc  m_CurrentUpdateFunc = nullptr;
    std::queue<SpellUpdateFunc> m_SpellUpdateQueue;
protected:
    AudioController* m_AudioControllerPtr = AudioController::GetInstance();
    int m_SpellTarget = 0; // 1 if A, -1 if B
    float m_TotalTime = 0.0f;

    std::string m_TexturePath;

    void Next();

    void OnUpdate(const float& dt) override;

    void QueueUpdateFunction(SpellUpdateFunc func);

    void QueueMoveEvent(glm::vec3 startPos, glm::vec3 endPos, float travelTime)
    {
        glm::vec3 direction = endPos - startPos;

        QueueUpdateFunction(
            [this, startPos, direction, travelTime](float dt)
            {
                if (m_TotalTime >= travelTime)
                {
                    Next();
                    return;
                }
                float progress = m_TotalTime / travelTime;

                this->position.x = startPos.x + direction.x * progress;
                this->position.y = startPos.y + direction.y * progress;
            }
        );
    }

    void QueueWaitTillFrameEvent(bool doNextCol = false,bool waitLastFrame = true, int targetFrame = -1)
    {
        QueueUpdateFunction(
            [this, doNextCol, waitLastFrame , targetFrame](float dt)
            {
                int _target = targetFrame;
                int currentRow = this->GetCurrentAnimationRow() - 1;
                int lastFrame = this->GetAnimationColumn(currentRow);

                if (waitLastFrame || _target == -1) _target = lastFrame;

                int curFrame = this->GetCurrentAnimationColumn();
                if (curFrame == _target)
                {
                    if (doNextCol) this->SetSpriteByIndex(currentRow + 1, 0 , true);
                    Next();
                    return;
                }
            }
        );
    }

    void QueueFadeOutEvent(float t)
    {
        QueueUpdateFunction([this, t](float dt)
            {
                this->color.a = 1.0f - (m_TotalTime / t);
                if (m_TotalTime >= t)
                {
                    Next();
                }
            });
    }

    void QueueWaitEvent(float t)
    {
        QueueUpdateFunction([this,t](float dt)
            {
                if (m_TotalTime >= t)
                {
                    Next();
                }
            });
    }

    void QueueWaitTriggerEvent()
    {
        QueueUpdateFunction([this](float dt)
            {
                if (this->Trigger == true)
                {
                    Next();
                }
                else
                {
                    m_SpellState = SpellObjectState::WaitTrigger;
                }
            });
    }

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

    void Activate() override;
   
};