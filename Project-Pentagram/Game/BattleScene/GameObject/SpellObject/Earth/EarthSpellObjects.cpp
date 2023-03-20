#include "EarthSpellObjects.h"
#include "Engine/IGameObjectManager.h"
#include "Engine/GameStateController.h"
#include <vector>

BaseSpellObject* EarthSpellObject::CreateSpellObject(int index, CasterPosition target)
{
    std::cout << "CREATE SPELL " << index << "****************************\n";

    BaseSpellObject* object = nullptr;
    switch (index)
    {
    case 0:
        object = new EarthSpell1(target);
        break;
    case 1:
        object = new EarthSpell2(target);
        break;
    case 2:
        object = new EarthSpell3(target);
        break;
    case 3:
        object = new EarthSpell4(target);
        break;
    case 4:
        object = new EarthSpell5(target);
        break;
    case 5:
        object = new EarthSpell6(target);
        break;
    case 6:
        object = new EarthSpell7(target);
        break;
    case 7:
        object = new EarthSpell8(target);
        break;
    case 8:
        object = new EarthSpell9(target);
        break;
    }
    return object;
}


void EarthSpell1::Initialize()
{
    std::cout << "Earthball::Init\n";
    float size = 300.0f;
    float speed = 10.0f;
    float startX = (CASTER_POSITION_X - 100.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-CASTER_POSITION_X + size / 4) * m_SpellTarget; // Assume B recieve
    float yPos = CASTER_POSITION_Y - 10.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };
    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };

    this->position = startPos;
    this->SetIsAnimationObject(true);
    this->SetAnimationPlayTime(0.35f);

    //Move A to B
    glm::vec3 direction = endPos - startPos;
    float travelTime = 1.0f;

    QueueWaitTillFrameEvent(true);
    m_AudioControllerPtr->PlaySFX("Audio/SFX/Gameplay/Spell/Fire/sfx_gameplay_fire_shooting_generic.wav", 1.0f);
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void EarthSpell2::Initialize()
{
    float size = 320.0f;
    float startX = (CASTER_POSITION_X - size) * m_SpellTarget; // Assume A shooter
    float endX = (-540.0f + size / 4) * m_SpellTarget;
    float yPos = -size / 2;
    this->scale = { size * 2 * -m_SpellTarget, size, 1.0f };
    this->position = { startX, yPos, 1.0f };
    this->SetIsAnimationObject(true);


    glm::vec3 startPos = { startX ,yPos,0.0f };
    glm::vec3 endPos = { endX ,yPos,0.0f };
    float travelTime = 1.5f;


    float timePerFrame = 0.15f;
    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent(true);

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueWaitTillFrameEvent(true);

    QueueWaitEvent(timePerFrame* 2);

    QueueHitEvent();

    QueueWaitEvent(timePerFrame);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationObject(false);
            Next();
        }
    );

    QueueWaitEvent(1.0f);

    QueueDoneEvent();
}

void EarthSpell3::Initialize()
{
    float size = 480.0f;
    float xPos = (-CASTER_POSITION_X) * m_SpellTarget; // Assume A shooter
    float yPos = (320.0f - size) / 2.0f;
    this->scale = { size / 2, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->SetIsAnimationObject(true);

    float timePerFrame = 0.15f;


    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent();

    QueueHitEvent();

    QueueDoneEvent();
}

void EarthSpell4::Initialize()
{
    float size = 320.0f;
    float startX = (CASTER_POSITION_X - size - 100.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-540.0f + size / 4) * m_SpellTarget;
    float yPos = -size / 2;
    this->scale = { size * 2 * -m_SpellTarget, size, 1.0f };
    this->position = { startX, yPos, 1.0f };
    this->SetIsAnimationObject(true);

    float timePerFrame = 0.15f;

    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };
    float travelTime = 0.5f;


    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent(true);
    QueueWaitEvent(timePerFrame);
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void EarthSpell5::Initialize()
{
    float size = 320.0f;
    float xPos = CASTER_POSITION_X * m_SpellTarget; // Assume A shooter // How to Flip m_SpellTarget
    float yPos = -160.0f;
    this->scale = { size * 2, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);

    float timePerFrame = 0.15f;

    this->SetAnimationPlayTime(timePerFrame);
    
    QueueWaitTillFrameEvent(true);

    QueueHitEvent();

    QueueWaitTillFrameEvent();

    QueueDoneEvent();
}

void EarthSpell6::Initialize()
{
    std::cout << "--------------- CREATED SPELL_6 --------------\n";
    float size = 640.0f;
    float xPos = (-CASTER_POSITION_X) * m_SpellTarget; // Assume A shooter
    float yPos = (320.0f - size) / 2.0f;
    this->scale = { size, size / 2.0f, 1.0f };
    this->position = { xPos, yPos, 1.0f };

    // Don't Play animation
    this->SetIsAnimationObject(false);
    this->SetSpriteByIndex(0, 0);

    float timePerFrame = 0.15f;


    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTriggerEvent();

    // If WaitTriggerEvent is done -> DO ANIMATION
    this->SetIsAnimationObject(true);
    QueueWaitTillFrameEvent(true);

    QueueHitEvent();

    QueueDoneEvent();
}

void EarthSpell7::Initialize()
{
    QueueHitEvent();
    QueueDoneEvent();
}

void EarthSpell8::Initialize()
{
    QueueHitEvent();
    QueueDoneEvent();
}

void EarthSpell9::Initialize()
{
    QueueHitEvent();
    QueueDoneEvent();
}