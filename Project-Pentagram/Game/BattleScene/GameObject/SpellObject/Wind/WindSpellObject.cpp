#include "WindSpellObjects.h"
#include "Engine/IGameObjectManager.h"
#include "Engine/GameStateController.h"
#include <vector>

BaseSpellObject* WindSpellObject::CreateSpellObject(int index, CasterPosition target)
{
    BaseSpellObject* object = nullptr;
    switch (index)
    {
    case 0:
        object = new WindSpell1(target);
        break;
    case 1:
        object = new WindSpell2(target);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        object = new WindSpell3(target);
        break;
    }
    return object;
}

void WindSpell1::Initialize()
{
    std::cout << "Windball::Init\n";
    float size = 300.0f;
    float speed = 10.0f;
    float startX = (CASTER_POSITION_X - 100.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-CASTER_POSITION_X + size / 4) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };
    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };
    float travelTime = 0.5f;

    this->position = startPos;
    this->SetAnimationPlayTime(0.1f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);

    m_AudioControllerPtr->PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_water_shooting_generic.wav", 1.0f);
    QueueWaitTillFrameEvent(true);
    QueueWaitEvent(0.5f);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationLoop(true);
            Next();
        }
    );
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell2::Initialize()
{
    std::cout << "Windball::Init\n";
    float size = 300.0f;
    float speed = 10.0f;
    float startX = (CASTER_POSITION_X - 100.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-CASTER_POSITION_X + size / 4) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };
    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };
    float travelTime = 0.75f;

    this->position = startPos;
    this->SetAnimationPlayTime(0.1f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    m_AudioControllerPtr->PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_water_shooting_generic.wav", 1.0f);
    QueueWaitEvent(0.5f);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(1, 0, true);
            Next();
        }
    );
    QueueMoveEvent(startPos, endPos, travelTime);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(2, 0, true);
            Next();
        }
    );
    QueueWaitTillFrameEvent();

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell3::Initialize()
{
    std::cout << "Windball::Init\n";
    float size = 400.0f;
    float speed = 10.0f;
    float yPos = -200.0f;
    this->scale = { -size * m_SpellTarget, size / 2.0f, 1.0f };
    float travelTime = 0.75f;

    this->position = { (-CASTER_POSITION_X) * m_SpellTarget, yPos, 0.0f };
    this->SetAnimationPlayTime(0.15f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    m_AudioControllerPtr->PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_water_shooting_generic.wav", 1.0f);
    QueueWaitTillFrameEvent(true);
    QueueWaitEvent(1.25f);

    QueueHitEvent();
    QueueDoneEvent();
}