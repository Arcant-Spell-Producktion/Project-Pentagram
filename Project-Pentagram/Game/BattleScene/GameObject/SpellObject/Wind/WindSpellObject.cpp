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
        object = new WindSpell3(target);
        break;
    case 3:
        object = new WindSpell4(target);
        break;
    case 4:
        object = new WindSpell5(target);
        break;
    case 5:
        object = new WindSpell6(target);
        break;
    case 6:
        object = new WindSpell7(target);
        break;
    case 7:
        object = new WindSpell8(target);
        break;
    case 8:
        object = new WindSpell9(target);
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
    float endX = (-CASTER_POSITION_X) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };
    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };
    float travelTime = 0.5f;

    this->position = startPos;
    this->SetAnimationPlayTime(0.1f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
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
    float endX = (-CASTER_POSITION_X) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };
    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };
    float travelTime = 0.75f;

    this->position = startPos;
    this->SetAnimationPlayTime(0.1f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
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
    std::cout << "WindStorm::Init\n";
    float size = 400.0f;
    float speed = 10.0f;
    float yPos = -200.0f;
    this->scale = { -size * m_SpellTarget, size / 2.0f, 1.0f };

    this->position = { (-CASTER_POSITION_X) * m_SpellTarget, yPos, 0.0f };
    this->SetAnimationPlayTime(0.2f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
    QueueWaitTillFrameEvent(true);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetAnimationPlayTime(0.1f);
            Next();
        }
    );
    QueueWaitEvent(1.25f);

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell4::Initialize()
{
    std::cout << "WindTornado::Init\n";
    float size = 500.0f;
    float speed = 10.0f;
    float startX = (CASTER_POSITION_X - 100.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-CASTER_POSITION_X) * m_SpellTarget * 2.0f; // Assume B recieve
    float yPos = -75.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };
    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };
    float travelTime = 1.0f;

    this->position = startPos;
    this->SetAnimationPlayTime(0.15f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
    QueueWaitTillFrameEvent(true);
    QueueWaitEvent(0.5f);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(2, 0, true);
            Next();
        }
    );
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell5::Initialize()
{
    std::cout << "Wind_DanceOfDyrad::Init\n";
    float size = 300.0f;
    float speed = 10.0f;
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };

    this->position = { (CASTER_POSITION_X) * m_SpellTarget, yPos, 0.0f };
    this->SetAnimationPlayTime(0.15f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);


    ParticleProperty windProp;
    windProp.position = { 900.0f * -m_SpellTarget, 400.0f };
    windProp.positionVariation = { 400.0f,0.0f };
    windProp.colorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
    windProp.colorEnd = { 1.0f, 1.0f, 1.0f, 1.0f };
    windProp.sizeBegin = windProp.sizeEnd = 80.0f;
    windProp.sizeVariation = 5.0f;
    windProp.rotation = m_SpellTarget == -1 ? -135.0f : -45.0f;
    windProp.rotationVariation = 0.0f;
    windProp.velocity = { -500.0f * m_SpellTarget, -550.0f };
    windProp.velocityVariation = { 100.0f * m_SpellTarget, 50.0f };
    windProp.lifeTime = 1.5f;

    m_LeafParticle = GameStateController::GetInstance().currentScene->CreateParticle(windProp);
    m_LeafParticle->SetTexture("Sprites/Spell/Wind/spell_sprite_wind5_particle.png");
    m_LeafParticle->SetIsAnimationObject(true);
    m_LeafParticle->SetIsFixRotation(true);
    m_LeafParticle->SetIsAnimationLoop(true);
    m_LeafParticle->SetSpawnTime(0.1f);

    this->SetChildRenderFront(m_LeafParticle);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
    QueueWaitTillFrameEvent(true);

    QueueWaitEvent(2.5f);

    QueueUpdateFunction(
        [this](float dt)
        {
            m_LeafParticle->SetSpawnTime(99);
            Next();
        });

    QueueWaitEvent(1.0f);

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell6::Initialize()
{
    auto scene = GameStateController::GetInstance().currentScene;

    std::cout << "WindTundra::Init\n";
    float size = 500.0f;
    float speed = 10.0f;
    float yPos = -60.0f;
    this->scale = { size * m_SpellTarget, size, 1.0f };

    this->position = { (-CASTER_POSITION_X) * m_SpellTarget, yPos, 0.0f };
    this->SetAnimationPlayTime(0.15f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
    QueueUpdateFunction(
        [this, scene](float dt)
        {
            scene->GetCamera()->Shake(0.5f, 30, { 10.0f, 0.0f });
            Next();
        });
    QueueWaitTillFrameEvent(false, false, 8);
    QueueUpdateFunction(
        [this, scene](float dt)
        {
            scene->GetCamera()->Shake(0.5f, 40, { 30.0f, 30.0f });
            Next();
        });
    QueueWaitTillFrameEvent(false);

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell7::Initialize()
{
    auto scene = GameStateController::GetInstance().currentScene;

    std::cout << "WindFairy::Init\n";
    float size = 600.0f;
    float speed = 10.0f;
    float yPos = -40.0f;
    this->scale = { size * m_SpellTarget, size, 1.0f };

    this->position = { (-CASTER_POSITION_X) * m_SpellTarget, yPos, 0.0f };
    this->SetAnimationPlayTime(0.15f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
    QueueWaitTillFrameEvent(false);

    QueueWaitTriggerEvent();
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetIsAnimationObject(true);
            this->SetAnimationPlayTime(0.1f);
            Next();
        }
    );

    QueueUpdateFunction(
        [this, scene](float dt)
        {
            this->SetSpriteByIndex(1, 0, true);
            scene->GetCamera()->Shake(0.1f * this->GetAnimationColumn(1), 50, { 30.0f, 30.0f });
            Next();
        }
    );

    QueueWaitEvent(0.1f * this->GetAnimationColumn(1));

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell8::Initialize()
{
    auto scene = GameStateController::GetInstance().currentScene;

    std::cout << "WindDragon::Init\n";
    float sizeX = 1750.0f;
    float sizeY = 640.0f;
    float speed = 10.0f;
    float yPos = -50.0f;
    float offset = 125.0f;
    this->scale = { -sizeX * m_SpellTarget, sizeY, 1.0f };

    this->position = { (-CASTER_POSITION_X + sizeX / 2.0f - offset) * m_SpellTarget, yPos, 0.0f };
    this->SetAnimationPlayTime(0.15f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
    QueueWaitTillFrameEvent(true);
    QueueWaitTillFrameEvent(false);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(2, 0, true);
            Next();
        }
    );

    QueueWaitEvent(0.25f);
    QueueUpdateFunction(
        [this, scene](float dt)
        {
            scene->GetCamera()->Shake(1.75f, 45, { 100.0f, 50.0f });
            Next();
        });
    QueueWaitEvent(1.75f);

    QueueWaitTillFrameEvent(true);
    QueueWaitTillFrameEvent(false);

    QueueWaitEvent(0.25f);

    QueueHitEvent();
    QueueDoneEvent();
}

void WindSpell9::Initialize()
{
    std::cout << "WindChaos::Init\n";
    
    auto scene = GameStateController::GetInstance().currentScene;

    this->color.a = 0.0f;

    float size = 700.0f;
    float speed = 10.0f;
    float yPos = 0.0f;
    this->scale = { -size * m_SpellTarget, size, 1.0f };

    this->position = { (-CASTER_POSITION_X) * m_SpellTarget, yPos, 0.0f };
    this->SetAnimationPlayTime(0.15f);
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);

    ParticleProperty particleProp;
    particleProp.position = { 250.0f * m_SpellTarget, 400.0f };
    particleProp.positionVariation = { 500.0f,0.0f };
    particleProp.colorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
    particleProp.colorEnd = { 1.0f, 1.0f, 1.0f, 1.0f };
    particleProp.rotation = 15.0f;
    particleProp.rotationVariation = 0.0f;
    particleProp.velocity = { -600.0f * m_SpellTarget, -650.0f };
    particleProp.velocityVariation = { 100.0f * m_SpellTarget, 50.0f };
    particleProp.lifeTime = 1.5f;

    particleProp.sizeBegin = particleProp.sizeEnd = 150.0f;
    m_WindParticle = GameStateController::GetInstance().currentScene->CreateParticle(particleProp);
    if (m_SpellTarget == -1)
    {
        m_WindParticle->SetTexture("Sprites/Spell/Wind/spell_sprite_wind9_particle.png");
    }
    else
    {
        m_WindParticle->SetTexture("Sprites/Spell/Wind/spell_sprite_wind9_particle_flip.png");
    }
    m_WindParticle->SetIsAnimationObject(true);
    m_WindParticle->SetIsFixRotation(true);
    m_WindParticle->SetIsAnimationLoop(true);
    m_WindParticle->SetSpawnTime(0.15f);

    particleProp.rotation = m_SpellTarget == -1 ? -135.0f : -45.0f;
    particleProp.sizeBegin = particleProp.sizeEnd = 90.0f;
    //m_LeafParticle.sizeVariation = 5.0f;
    m_LeafParticle = GameStateController::GetInstance().currentScene->CreateParticle(particleProp);
    m_LeafParticle->SetTexture("Sprites/Spell/Wind/spell_sprite_wind5_particle.png");
    m_LeafParticle->SetIsAnimationObject(true);
    m_LeafParticle->SetIsFixRotation(true);
    m_LeafParticle->SetIsAnimationLoop(true);
    m_LeafParticle->SetSpawnTime(99);

    particleProp.rotation = m_SpellTarget == 1 ? -135.0f : -45.0f;
    particleProp.sizeBegin = particleProp.sizeEnd = 250.0f;
    m_FireParticle = GameStateController::GetInstance().currentScene->CreateParticle(particleProp);
    m_FireParticle->SetTexture("Sprites/Spell/Fire/spell_fire_3.png");
    m_FireParticle->SetIsAnimationObject(true);
    m_FireParticle->SetIsFixRotation(true);
    m_FireParticle->SetIsAnimationLoop(false);
    m_FireParticle->SetSpawnTime(99);

    particleProp.sizeBegin = particleProp.sizeEnd = 75.0f;
    m_WaterParticle = GameStateController::GetInstance().currentScene->CreateParticle(particleProp);
    m_WaterParticle->SetTexture("Sprites/Spell/Water/spell_water_8-1.png");
    m_WaterParticle->SetIsAnimationObject(true);
    m_WaterParticle->SetIsFixRotation(true);
    m_WaterParticle->SetIsAnimationLoop(false);
    m_WaterParticle->SetSpawnTime(99);

    this->SetChildRenderBack(m_WindParticle);
    this->SetChildRenderBack(m_FireParticle);
    this->SetChildRenderBack(m_WaterParticle);
    this->SetChildRenderBack(m_LeafParticle);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);

    QueueWaitEvent(1.0f);

    QueueUpdateFunction(
        [this](float dt)
        {
            m_LeafParticle->SetSpawnTime(0.1f);
            Next();
        });

    QueueWaitEvent(1.0f);
    QueueUpdateFunction(
        [this](float dt)
        {
            m_WindParticle->SetSpawnTime(99);
            m_WaterParticle->SetSpawnTime(0.1f);
            Next();
        });

    QueueUpdateFunction(
        [this, scene](float dt)
        {
            scene->GetCamera()->Shake(2.5f, 80, { 30.0f, 30.0f });
            Next();
        });

    QueueWaitEvent(0.5f);
    QueueUpdateFunction(
        [this](float dt)
        {
            m_FireParticle->SetSpawnTime(0.1f);
            m_LeafParticle->SetSpawnTime(99);
            Next();
        });

    QueueWaitEvent(1.5f);

    QueueUpdateFunction(
        [this](float dt)
        {
            m_WaterParticle->SetSpawnTime(99);
            Next();
        });

    QueueWaitEvent(0.5f);

    QueueUpdateFunction(
        [this](float dt)
        {
            m_FireParticle->SetSpawnTime(99);
            m_WaterParticle->SetSpawnTime(99);
            m_LeafParticle->SetSpawnTime(99);
            Next();
        });

    QueueWaitEvent(1.0f);

    QueueUpdateFunction(
        [this](float dt)
        {
            this->color.a = 1.0f;
            this->SetSpriteByIndex(0, 0, false);
            Next();
        });
    
    QueueWaitTillFrameEvent(false, false, 3);
    QueueUpdateFunction(
        [this, scene](float dt)
        {
            scene->GetCamera()->Shake(0.75f, 40, { 150.0f,100.0f });
            Next();
        });
    QueueWaitTillFrameEvent(false);

    QueueHitEvent();
    QueueDoneEvent();
}