#include "FireSpellObjects.h"
#include "Engine/IGameObjectManager.h"
#include "Engine/GameStateController.h"
#include <vector>

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
    case 2:
        object = new FireSpell3(target);
        break;
    case 3:
        object = new FireSpell4(target);
        break;
    case 4:
        object = new FireSpell5(target);
        break;    
    case 5:
        object = new FireSpell6(target);
        break;
    case 6:
        object = new FireSpell7(target);
        break;
    case 7:
        object = new FireSpell8(target);
        break;
    case 8:
        object = new FireSpell9(target);
        break;
    }
    return object;
}

void FireSpell1::Initialize()
{
    std::cout << "Fireball::Init\n";
    float size = 300.0f;
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

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void FireSpell2::Initialize()
{
    std::cout << "FireArrow::Init\n";
    float size = 400.0f;
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

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void FireSpell3::Initialize()
{
    this->color.a = 0.0f;

    ParticleProperty particleProp;
    particleProp.position = { 0.0f, 600.0f};
    particleProp.colorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
    particleProp.colorEnd = { 1.0f, 1.0f, 1.0f, 1.0f };
    particleProp.sizeBegin = particleProp.sizeEnd = 600.0f;
    particleProp.rotation = m_SpellTarget == 1?-135.0f:-45.0f;
    particleProp.rotationVariation = 0.0f;
    particleProp.velocity = { -700.0f * m_SpellTarget, -700.0f };
    particleProp.velocityVariation = { -700.0f * m_SpellTarget, 100.0f };
    particleProp.lifeTime = 1.5f;
    ParticleSystem* particle = GameStateController::GetInstance()->currentScene->CreateParticle(particleProp);
    particle->SetTexture(this->m_TexturePath);
    particle->SetIsAnimationObject(true);
    particle->SetIsFixRotation(true);
    particle->SetSpawnTime(0.25f);


    this->SetChildRenderFront(particle);

    QueueWaitEvent(lifeTime);

    QueueHitEvent();

    QueueWaitEvent(spawnTime * amount);

    QueueUpdateFunction(
        [this, particle](float dt)
        {
            particle->SetSpawnTime(99);
            Next();
        });

    QueueWaitEvent(lifeTime);

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

    QueueUpdateFunction(
        [this, count](float dt)
        {
            if (m_TotalTime >= 2.0f)
            {
                Next();
                return;
            }

            this->SetIsAnimationObject(false);
            this->SetSpriteByValue(1, count);

            localTimer += dt;
            if (localTimer >= 0.1f)
            {
                std::cout << "\tFLIP\n";
                this->scale.x = this->scale.x * -1;
                localTimer = 0.0f;
            }
        }
    );

    QueueDoneEvent();
}

void FireSpell5::Initialize()
{
    auto scene = GameStateController::GetInstance()->currentScene;
    
    float spawnDelay = 0.15f;

    float xPos = (-700.0f) * m_SpellTarget; // Assume A shooter
    float yPos = 0.0f;
    float fps = 0.1f;


    for (size_t i = 0; i < m_SpawnCount; i++)
    {
        int flip = i % 2 == 0 ? 1 : -1;
        
        auto obj = scene->CreateGameObject("snap");
        obj->SetTexture(m_TexturePath);
        obj->position = { xPos,-160.0f,0.0f };
        obj->scale = { 640.0f * flip,320.0f,1.0f };
        obj->SetIsAnimationObject(false);
        obj->SetAnimationPlayTime(0.1f);
        obj->SetActive(false);

        this->SetChildRenderFront(obj);
        m_objectList.push_back(obj);
        std::cout << "Snap create: " << i << "\n";

    }

    QueueUpdateFunction(
        [this,  scene , spawnDelay,xPos](float dt)
        {
            if (m_DoneCount < m_SnapCount)
            {
                m_localTimer += dt;
                if (m_localTimer > spawnDelay)
                {
                    std::cout << "Snap spawn: " << m_SnapCount << "\n";
                    auto obj = this->m_objectList[m_SnapCount % m_SpawnCount];
                    obj->SetActive(true);
                    obj->SetIsAnimationObject(true);
                    m_SnapCount++;

                    m_localTimer = 0;
                }
            }

            for (auto obj : m_objectList)
            {
                if (obj->GetCurrentAnimationColumn() == 9 && obj->IsActive())
                {
                    scene->GetCamera()->Shake( 0.25f , 3, { 50.0f,50.0f });
                    obj->SetActive(false);
                    obj->SetIsAnimationObject(false);
                    m_DoneCount++;
                }
            }
            std::cout << "Snap Done: " << m_DoneCount << "\n";

            if (m_DoneCount >= m_SpawnCount)
            {
                Next();
            }
        }
    );

    QueueHitEvent();

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

    QueueUpdateFunction(
        [this](float dt)
        {
            if (this->GetCurrentAnimationColumn() == 8)
            {
                this->SetSpriteByIndex(0, 8);
                //this->SetIsAnimationObject(false);
                Next();
                return;
            }
        }
    );

    QueueHitEvent();

    QueueWaitEvent(timePerFrame);

    int spinCount = 2;
    float spinTime = spinCount * timePerFrame * 6;
    QueueUpdateFunction(
        [this, spinTime](float dt)
        {
            auto scene = GameStateController::GetInstance()->currentScene;
            scene->GetCamera()->Shake(spinTime, 16, { 50.0f,0.0f });
            this->SetIsAnimationObject(true);
            this->SetSpriteByIndex(1, 0);
            Next();
        }
    );

    QueueWaitEvent(spinTime);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(2, 0);
            Next();
        }
    );

    QueueUpdateFunction(
        [this](float dt)
        {
            if (this->GetCurrentAnimationColumn() == 2)
            {
                this->SetSpriteByIndex(2, 2);
                this->SetIsAnimationObject(false);
                Next();
            }
        }
    );

    QueueWaitEvent(timePerFrame);
    QueueDoneEvent();

}

void FireSpell7::Initialize()
{
    std::cout << "Meteor::Init\n";
    float size = 800.0f;
    float speed = 10.0f;
    float startX = (600.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-700.0f + size / 4) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget,size,1.0f };
    glm::vec3 startPos = { startX ,yPos + 1600.0f ,0.0f };
    glm::vec3 endPos = { endX ,yPos + 160.0f,0.0f };

    this->position = startPos;
    this->SetIsAnimationObject(true);

    //Move A to B
    glm::vec3 direction = endPos - startPos;
    float travelTime = 1.0f;

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();

    float shakeTime = 1.5f;
    QueueUpdateFunction(
        [this, shakeTime](float dt)
        {
            auto scene = GameStateController::GetInstance()->currentScene;
            scene->GetCamera()->Shake(shakeTime, 30, { 300.0f, 100.0f });
            Next();

        }
    );

    QueueWaitEvent(shakeTime);

    QueueDoneEvent();
}

void FireSpell8::Initialize()
{
    std::cout << "FireDragon::Init\n";
    float size = 1000.0f;
    float speed = 2.0f;
    float startX = (400.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-700.0f + size / 2) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    float animSpeed = 1/12.0f;
    this->scale = { -size * m_SpellTarget,size / 2,1.0f };
    glm::vec3 startPos = { startX ,yPos,0.0f };
    glm::vec3 endPos = { endX ,yPos,0.0f };

    this->position = startPos;
    this->SetAnimationPlayTime(animSpeed);
    this->SetIsAnimationObject(true);

    float distant = glm::distance(startX, endX);
    float travelTime = distant / (distant * speed);

    int col = this->GetAnimationColumn(0) - 1;

    QueueWaitEvent(col * animSpeed);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(1, 0);
            Next();
            return;
        }
    );

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();

    glm::vec3 newEndPos = endPos;
    newEndPos.x -= size * m_SpellTarget;

    float newDistant = glm::distance(startPos, newEndPos);

    startPos = endPos;
    endPos = newEndPos;

    travelTime += travelTime * (distant / newDistant);

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueDoneEvent();
}

void FireSpell9::Initialize()
{
    std::cout << "Hell::Init\n";
    auto scene = GameStateController::GetInstance()->currentScene;

    float size = 2000.0f;
    float speed = 2.0f;
    float startX = (-280.0f) * m_SpellTarget; // Assume A shooter
    float yPos = -160.0f;
    float animSpeed = 1 / 12.0f;
    this->scale = { -size * m_SpellTarget,size / 3,1.0f };
    this->position = { startX ,yPos,0.0f };
     
    this->SetAnimationPlayTime(animSpeed);
    this->SetIsAnimationObject(true);

    int col = this->GetAnimationColumn(0) - 1;

    QueueWaitEvent(col * animSpeed);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(1, 0);
            Next();
            return;
        }
    );

    QueueHitEvent();

    float blastTime = 1.5f;

    QueueUpdateFunction(
        [this, scene, blastTime](float dt)
        {
            scene->GetCamera()->Shake(blastTime, 25, { 50.0f,100.0f });
            Next();
            return;
        }
    );

    QueueWaitEvent(1.5f);

    QueueDoneEvent();
}
