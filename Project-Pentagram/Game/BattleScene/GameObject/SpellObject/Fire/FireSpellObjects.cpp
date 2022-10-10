#include "FireSpellObjects.h"
#include "Engine/IGameObjectManager.h"
#include "Engine/GameStateController.h"

BaseSpellObject* FireSpellObject::CreateSpellObject(int index, CasterPosition target)
{
    BaseSpellObject* object = nullptr;
    switch (index)
    {
    case 0:
        object = new FireSpell1(target);
        break;
    case 1:
        object = new FireSpell2(target);
        break;
   /* case 2:
        break;*/
    case 3:
        object = new FireSpell4(target);
        break;
        /*
    case 4:
        break;
        */
    case 5:
        object = new FireSpell6(target);
        break;
        /*
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;*/
    default:
        object = new FireSpell1(target);
        break;
    }
    return object;
}

void FireSpell1::Initialize()
{
    std::cout << "Fireball::Init\n";
    float size = 800.0f;
    float speed = 10.0f;
    float startX = (600.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-700.0f + size / 4) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget,size,1.0f };
    glm::vec3 startPos = { startX ,yPos,0.0f };
    glm::vec3 endPos = { endX ,yPos,0.0f };

    this->position = startPos;
    this->SetIsAnimationObject(true);

    //Move A to B
    glm::vec3 direction = endPos - startPos;
    float travelTime = 1.0f;

    QueueUpdateFunction(
        [this, startPos, direction, travelTime](float dt)
        {
            std::cout << "\tSpell::Move\n";
            if (m_TotalTime >= travelTime)
            {
                Next();
                return;
            }
            float progress = m_TotalTime / travelTime;

            this->position.x = startPos.x + direction.x * progress;
        }
    );

    QueueHitEvent();
    QueueDoneEvent();
}

void FireSpell2::Initialize()
{
    std::cout << "FireArrow::Init\n";
    float size = 800.0f;
    float speed = 10.0f;
    float startX = (600.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-700.0f + size / 4) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget,size / 2,1.0f };
    glm::vec3 startPos = { startX ,yPos,0.0f };
    glm::vec3 endPos = { endX ,yPos,0.0f };

    this->position = startPos;
    this->SetIsAnimationObject(true);

    //Move A to B
    glm::vec3 direction = endPos - startPos;
    float travelTime = 1.0f;

    QueueUpdateFunction(
        [this, startPos, direction, travelTime](float dt)
        {
            std::cout << "\tSpell::Move\n";
            if (m_TotalTime >= travelTime)
            {
                Next();
                return;
            }
            float progress = m_TotalTime / travelTime;

            this->position.x = startPos.x + direction.x * progress;
        }
    );

    QueueHitEvent();
    QueueDoneEvent();
}

void FireSpell4::Initialize()
{
    std::cout << "FireWall::Init\n";
    float size = 640.0f;
    float xPos = (-700.0f) * m_SpellTarget; // Assume A shooter
    float yPos = 0.0f;
    this->scale = { size/2 ,size,1.0f };
    this->position = { -700.0f * m_SpellTarget,yPos,1.0f };
    this->SetIsAnimationObject(true);
    
    float timePerFrame = 0.1f;
    int count = this->GetAnimationColumn(0);

    this->SetAnimationPlayTime(timePerFrame);

    float totalTime = timePerFrame * (count-1);

    QueueUpdateFunction(
        [this, totalTime](float dt)
        {
            if (m_TotalTime >= totalTime)
            {
                Next();
                return;
            }
        }
    );

    QueueHitEvent();

    float localTimer = 0.0f;
    QueueUpdateFunction(
        [this, &localTimer, count](float dt)
        {
            

            if (m_TotalTime >= 2.0f)
            {
                Next();
                return;
            }

            this->SetIsAnimationObject(false);
            this->SetSpriteByValue(1, count);

            localTimer += dt;
            if (localTimer >= 0.25f)
            {
                this->scale.x = this->scale.x * -1;
                localTimer = 0.0f;
            }
        }
    );

    QueueDoneEvent();
}

void FireSpell6::Initialize()
{
    std::cout << "Fire Storm::Init\n";
    float size = 640.0f;
    float xPos = (-700.0f) * m_SpellTarget; // Assume A shooter
    float yPos = 0.0f;
    this->scale = { size / 2 ,size,1.0f };
    this->position = { -700.0f * m_SpellTarget,yPos,1.0f };
    this->SetIsAnimationObject(true);

    float timePerFrame = 0.1f;
    this->SetAnimationPlayTime(timePerFrame);

    int count = 0;
    count = this->GetAnimationColumn(0);
    float chargeTime = timePerFrame * (count - 1);
    QueueUpdateFunction(
        [this, chargeTime](float dt)
        {
            if (m_TotalTime >= chargeTime)
            {
                Next();
                return;
            }
        }
    );

    QueueHitEvent();

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByValue(1, 0);
            Next();
        }
    );

    float spinTime = 2.0f;
    QueueUpdateFunction(
        [this, spinTime](float dt)
        {
            if (m_TotalTime >= spinTime)
            {
                Next();
            }
        }
    );
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByValue(1, 0);
            Next();
        }
    );

    count = this->GetAnimationColumn(2);
    float endTime = timePerFrame * (count - 1);
    QueueUpdateFunction(
        [this, endTime](float dt)
        {
            if (m_TotalTime >= endTime)
            {
                Next();
            }
        }
    );
    QueueDoneEvent();
}
