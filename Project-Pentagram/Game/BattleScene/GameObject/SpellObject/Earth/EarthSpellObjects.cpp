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

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationObject(true);
            Next();
        }
    );

    QueueWaitTillFrameEvent(false, false, 5);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationObject(false);
            Next();
        }
    );
    QueueWaitEvent(1.0f);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationObject(true);
            Next();
        }
    );
    QueueWaitTillFrameEvent(false, true);

    QueueHitEvent();

    QueueDoneEvent();

}

void EarthSpell7::Initialize()
{
    float size = 320.0f;
    float xPos = (CASTER_POSITION_X - 200.0f) * m_SpellTarget;
    float yPos = -160.0f;
    this->scale = { size, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);
    float timePerFrame = 0.15f;
    this->SetAnimationPlayTime(timePerFrame);

    // Initialize Reflect Object
    reflectObj->SetTexture("Sprites/Spell/Earth/spell_earth_1.png");
    reflectObj->position = { this->scale.x / 2.0f, 0.0f, 0.0f };
    reflectObj->color.a = 0.0f;
    reflectObj->scale = { 320.0f, 320.0f, 1.0f };
    reflectObj->SetSpriteByIndex(0, 0);
    reflectObj->SetIsAnimationObject(false);
    reflectObj->SetAnimationPlayTime(0.15f);
    this->SetChildRenderFront(reflectObj);

    QueueWaitTillFrameEvent(false);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationLoop(true);
            this->SetSpriteByIndex(1, 0);

            Next();
        }
    );
    QueueWaitEvent(1.0f);

    QueueWaitTriggerEvent();

    QueueWaitEvent(2.0f);


    QueueUpdateFunction(
        [this](float dt)
        {
            reflectObj->SetIsAnimationObject(true);
            reflectObj->color.a = 1.0f;
            int currentRow = reflectObj->GetCurrentAnimationRow() - 1;
            int _target = reflectObj->GetAnimationColumn(currentRow);

            int curFrame = reflectObj->GetCurrentAnimationColumn();

            if (curFrame == _target)
            {
                reflectObj->SetSpriteByIndex(currentRow + 1, 0, true);

                Next();
                return;
            }
        }
    );

    float travelTime = 1.0f;
    glm::vec3 startPos = reflectObj->position;
    glm::vec3 endPos = { CASTER_POSITION_X + std::fabs(this->position.x), 0.0f, 0.0f};
    glm::vec3 direction = endPos - startPos;

    std::cout << startPos.x << " " << startPos.y << " " << startPos.z << std::endl;
    std::cout << endPos.x << " " << endPos.y << " " << endPos.z << std::endl;
    std::cout << direction.x << " " << direction.y << " " << direction.z << std::endl;

    QueueUpdateFunction(
        [this, startPos, direction, travelTime](float dt)
        {
            if (m_TotalTime >= travelTime)
            {
                Next();
                reflectObj->color.a = 0.0f;
                return;
            }
            float progress = m_TotalTime / travelTime;

            reflectObj->position.x = startPos.x + direction.x * progress;
            reflectObj->position.y = startPos.y + direction.y * progress;
        }
    );

    QueueHitEvent();
    
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationLoop(false);
            this->SetSpriteByIndex(2, 0);

            Next();
        }
    );
    QueueWaitTillFrameEvent();

    QueueDoneEvent();

}

void EarthSpell8::Initialize()
{
    float size = 320.0f;
    float xPos = (CASTER_POSITION_X - 200.0f) * -m_SpellTarget;
    float yPos = -160.0f;
    this->scale = { size, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);
    float timePerFrame = 0.15f;
    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent(false);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationLoop(true);
            this->SetSpriteByIndex(1, 0);

            Next();
        }
    );
    QueueWaitEvent(1.0f);

    QueueWaitTriggerEvent();

    QueueWaitEvent(1.0f);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationLoop(false);
            this->SetSpriteByIndex(2, 0);

            Next();
        }
    );
    QueueWaitTillFrameEvent();

    QueueHitEvent();
    QueueDoneEvent();
}

void EarthSpell9::Initialize()
{
    auto scene = GameStateController::GetInstance()->currentScene;

    float size = 640.0f;
    float xPos = CASTER_POSITION_X * -m_SpellTarget;
    float yPos = -320.0f;
    this->scale = { size * 2, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);

    float timePerFrame = 0.15f;
    this->SetAnimationPlayTime(timePerFrame);
    
    float blastTime = 1.5f;

    QueueUpdateFunction(
        [this, scene, blastTime](float dt)
        {
            scene->GetCamera()->Shake(blastTime, 25, { 50.0f,100.0f });
            Next();
        }
    );

    QueueUpdateFunction(
        [this](float dt)
        {
            int currentRow = this->GetCurrentAnimationRow() - 1;
            int currentColumn = this->GetCurrentAnimationColumn() - 1;
            int lastRow = this->GetAnimationRow();
            int lastColumn = this->GetAnimationColumn(currentRow);

            if (currentColumn == lastColumn - 1)
            {
                if (currentRow + 1 == lastRow)
                {
                    Next();
                    return;
                }
                this->SetSpriteByIndex(currentRow + 1, 0, true);
            }
        }
    );

    QueueWaitEvent(1.0f);

    QueueHitEvent();
    QueueDoneEvent();
}