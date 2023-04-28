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
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        object = new WindSpell1(target);
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
    float travelTime = 1.5f;

    this->position = startPos;
    this->SetIsAnimationObject(true);

    m_AudioControllerPtr->PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_water_shooting_generic.wav", 1.0f);
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}
