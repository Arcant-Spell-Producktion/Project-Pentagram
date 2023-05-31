#include "WaterSpellObjects.h"
#include "Engine/IGameObjectManager.h"
#include "Engine/GameStateController.h"
#include <vector>

BaseSpellObject* WaterSpellObject::CreateSpellObject(int index, CasterPosition target)
{
    BaseSpellObject* object = nullptr;
    switch (index)
    {
    case 0:
        object = new WaterSpell1(target);
        break;
    case 1:
        object = new WaterSpell2(target);
        break;
    case 2:
        object = new WaterSpell3(target);
        break;
    case 3:
        object = new WaterSpell4(target);
        break;
    case 4:
        object = new WaterSpell5(target);
        break;    
    case 5:
        object = new WaterSpell6(target);
        break;
    case 6:
        object = new WaterSpell7(target);
        break;
    case 7:
        object = new WaterSpell8(target);
        break;
    case 8:
        object = new WaterSpell9(target);
        break;
    }
    return object;
}

void WaterSpell1::Initialize()
{
    std::cout << "WaterBall::Init\n";
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

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_1.wav", 1.0f);
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void WaterSpell2::Initialize()
{
    float size = 320.0f;
    float startX = (440.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-540.0f + size / 4) * m_SpellTarget;
    float yPos = -size / 2;
    this->scale = { size * 2 * -m_SpellTarget, size, 1.0f };
    this->position = { startX, yPos, 1.0f };
    this->SetIsAnimationObject(true);

    float timePerFrame = 0.1f;

    glm::vec3 startPos = { startX, yPos, 0.0f };
    glm::vec3 endPos = { endX, yPos, 0.0f };
    float travelTime = 0.75f;


    this->SetAnimationPlayTime(timePerFrame);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_2.wav", 1.0f);
    QueueWaitTillFrameEvent(true);
    QueueWaitEvent(timePerFrame);
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void WaterSpell3::Initialize()
{
    float size = 640.0f;
    float xPos = (-CASTER_POSITION_X) * m_SpellTarget; // Assume A shooter
    float yPos = 0.0f;
    this->scale = { size / 2, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->SetIsAnimationObject(true);

    float timePerFrame = 0.15f;


    this->SetAnimationPlayTime(timePerFrame);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_3.wav", 1.0f);

    QueueWaitTillFrameEvent();

    QueueHitEvent();

    QueueDoneEvent();

}

void WaterSpell4::Initialize()
{
    std::cout << "Rebound Wave::Init\n";
    x_index = 0;
    float size = 640.0f;
    float yPos = -170.0f;
    this->scale = { size * -m_SpellTarget, size / 2, 1.0f };
    this->position = { x_Positions[x_index] * m_SpellTarget, yPos, 1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);
    
    float timePerFrame = 0.15f;

    this->SetAnimationPlayTime(timePerFrame);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_4.wav", 1.0f);
    QueueUpdateFunction(
        [this](float dt)
        {
            this->SetSpriteByIndex(0, 0);
            Next();
        }
    );
    QueueUpdateFunction(
        [this, yPos](float dt)
        {
            if (this->GetCurrentAnimationColumn() == 5)
            { 
                canMove = true;
            }
            else if(this->GetCurrentAnimationColumn() == 1 && canMove)
            {
                if (x_index < 3)
                {
                    float xPos = x_Positions[x_index] * m_SpellTarget;
                    x_index++;
                    this->position = { xPos ,yPos,1.0f };
                }
                else
                {
                    auto scene = GameStateController::GetInstance().currentScene;
                    scene->GetCamera()->Shake(0.5f, 8, { 50.0f,0.0f });
                    x_index = 2;
                    this->scale.x *= -1;
                    Next();
                }
                canMove = false;
            } 
        }
    );

    QueueUpdateFunction(
        [this, yPos](float dt)
        {
            if (this->GetCurrentAnimationColumn() == 5)
            {
                canMove = true;
            }
            else if (this->GetCurrentAnimationColumn() == 1 && canMove)
            {
                if (x_index > 0)
                {
                    x_index--;
                    float xPos = x_Positions[x_index] * m_SpellTarget;
                    this->position = { xPos ,yPos,1.0f };
                }
                else
                {
                    Next();
                }
                canMove = false;
            }
        }
    );

    QueueHitEvent();

    QueueDoneEvent();
}

void WaterSpell5::Initialize()
{
    float size = 320.0f;
    float xPos = (CASTER_POSITION_X) * m_SpellTarget; // Assume A shooter
    float yPos = -160.0f;
    this->scale = { size * 2, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);

    float timePerFrame = 0.15f;

    this->SetAnimationPlayTime(timePerFrame);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_5.wav", 1.0f);
    QueueWaitTillFrameEvent(true);
    
    QueueHitEvent();

    QueueWaitTillFrameEvent();

    QueueDoneEvent();

}

void WaterSpell6::Initialize()
{
    std::cout << "Water Beam::Init\n";
    float size = 400.0f;
    float xPos = (CASTER_POSITION_X - 300.0f) * m_SpellTarget; // Assume A shooter
    float yPos = -160.0f;
    this->scale = { size, size, 1.0f };
    this->position = { xPos, yPos, 1.0f };
    this->color.a = 0.0f;
    this->SetIsAnimationObject(false);
    float timePerFrame = 0.25f;

    auto scene = GameStateController::GetInstance().currentScene;
    for (size_t i = 0; i < 4; i++)
    {
        auto _section = scene->CreateGameObject("WaterBeam"+i);

        _section->scale = { size * -m_SpellTarget, size, 1.0f };
        _section->position.x = size * i * -m_SpellTarget;
        _section->SetTexture(this->m_TexturePath);
        _section->SetSpriteByIndex(i, 0);
        _section->SetIsAnimationObject(true);
        _section->SetAnimationPlayTime(timePerFrame);

        this->SetChildRenderFront(_section);
        m_Section.push_back(_section);
    }
    this->SetAnimationPlayTime(timePerFrame);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_6.wav", 1.0f);
    QueueUpdateFunction(
        [this, timePerFrame](float dt)
        {
            if (m_Section[3]->GetCurrentAnimationColumn() == 7)
            {
                for (size_t i = 0; i < 4; i++)
                {
                    m_Section[i]->SetSpriteByIndex(i + 4, 0,true);
                    m_Section[i]->SetAnimationPlayTime(timePerFrame / 2.0f);
                }
                Next();
                return;
            }
        }
    );

    QueueHitEvent();

    QueueWaitEvent(2.0f);

    QueueDoneEvent();

}

void WaterSpell7::Initialize()
{
    float size = 320.0f;
    float startX = (440.0f) * m_SpellTarget; // Assume A shooter
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

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_7.wav", 1.0f);
    QueueWaitTillFrameEvent(true);

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();

    QueueDoneEvent();
}

void WaterSpell8::Initialize()
{
    this->color.a = 0.0f;

    ParticleProperty windProp;
    windProp.position = { 0.0f, 400.0f };
    windProp.positionVariation = { 500.0f,0.0f };
    windProp.colorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
    windProp.colorEnd = { 1.0f, 1.0f, 1.0f, 1.0f };
    windProp.sizeBegin = windProp.sizeEnd = 180.0f;
    windProp.rotation = m_SpellTarget == 1 ? -135.0f : -45.0f;
    windProp.rotationVariation = 0.0f;
    windProp.velocity = { -600.0f * m_SpellTarget, -650.0f };
    windProp.velocityVariation = {100.0f * m_SpellTarget, 50.0f };
    windProp.lifeTime = 1.5f;

    m_WindParticle = GameStateController::GetInstance().currentScene->CreateParticle(windProp);
    m_WindParticle->SetTexture("Sprites/Spell/Water/spell_water_8-2.png");
    m_WindParticle->SetIsAnimationObject(true);
    m_WindParticle->SetIsFixRotation(true);
    m_WindParticle->SetIsAnimationLoop(true);
    m_WindParticle->SetSpawnTime(0.15f);

    this->SetChildRenderFront(m_WindParticle);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_8.wav", 1.0f);
    QueueWaitEvent(1.5f);

    QueueUpdateFunction(
        [this](float dt)
        {
            ParticleProperty hailProp;
            hailProp.position = { 100.0f, 200.0f };
            hailProp.positionVariation = { 250.0f,0.0f };
            hailProp.colorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
            hailProp.colorEnd = { 1.0f, 1.0f, 1.0f, 1.0f };
            hailProp.sizeBegin = hailProp.sizeEnd = 80.0f;
            hailProp.rotation = m_SpellTarget == 1 ? -125.0f : -35.0f;
            hailProp.rotationVariation = 0.0f;
            hailProp.velocity = { -750.0f * m_SpellTarget, -700.0f };
            hailProp.velocityVariation = { 100.0f, 100.0f };
            hailProp.lifeTime = 1.5f;

            m_HailParticle = GameStateController::GetInstance().currentScene->CreateParticle(hailProp);
            m_HailParticle->SetTexture("Sprites/Spell/Water/spell_water_8-1.png");
            m_HailParticle->SetIsAnimationObject(true);
            m_HailParticle->SetIsFixRotation(true);
            m_HailParticle->SetIsAnimationLoop(false);
            m_HailParticle->SetSpawnTime(0.075f);

            this->SetChildRenderFront(m_HailParticle);
            Next();
        });

    QueueHitEvent();

    QueueWaitEvent(3.0f);

    QueueUpdateFunction(
        [this](float dt)
        {
            m_WindParticle->SetSpawnTime(99);
            m_HailParticle->SetSpawnTime(99);
            Next();
        });

    QueueWaitEvent(2.5f);

    QueueDoneEvent();
}

void WaterSpell9::Initialize()
{
    auto scene = GameStateController::GetInstance().currentScene;

    float size = 1920.0f;
    float speed = 2.0f;
    float startX = (0.0f) * m_SpellTarget; // Assume A shooter
    float yPos = 0.0f;
    float animSpeed = 0.15f;
    this->scale = { -size * m_SpellTarget, size / 3, 1.0f };
    this->position = { startX, yPos, 0.0f };
     
    this->SetAnimationPlayTime(animSpeed);
    this->SetIsAnimationObject(false);
    this->color.a = 0.0f;

    int col = this->GetAnimationColumn(0) - 1;

    GameObject* _bubbleObj = scene->CreateGameObject("bubble");
    _bubbleObj->SetTexture("Sprites/Spell/Water/spell_water_9-2.png");
    _bubbleObj->scale = { 320.0f, 320.0f, 1.0f };
    _bubbleObj->position = { CASTER_POSITION_X * m_SpellTarget, -160.0f, 0.0f };
    _bubbleObj->SetAnimationPlayTime(animSpeed);
    _bubbleObj->SetIsAnimationObject(true);
    _bubbleObj->SetIsAnimationLoop(false);


    _bubbleObj->position -= this->position;
    this->SetChildRenderBack(_bubbleObj);

    int lastBubbleFrame = _bubbleObj->GetAnimationColumn(_bubbleObj->GetCurrentAnimationRow() - 1);

    m_AudioControllerPtr.PlaySFX("Audio/SFX/Gameplay/Spell/Water/sfx_gameplay_spell_water_9.wav", 1.0f);
    QueueUpdateFunction(
        [this, _bubbleObj, lastBubbleFrame](float dt)
        {
            int curFrame = _bubbleObj->GetCurrentAnimationColumn();
            if (curFrame == lastBubbleFrame)
            {
                this->SetIsAnimationObject(true);
                this->color.a = 1.0f;
                Next();
                return;
            }
        }
    );

    QueueWaitTillFrameEvent(true);

    QueueWaitEvent(animSpeed);

    QueueUpdateFunction(
        [this](float dt)
        {
            int lastFrame = this->GetAnimationColumn(1);

            int curFrame = this->GetCurrentAnimationColumn();
            if (curFrame == lastFrame)
            {
               this->SetSpriteByIndex(2, 0, true);
                Next();
                return;
            }
        }
    );

    float blastTime = 3.0f;

    QueueUpdateFunction(
        [this, scene, blastTime](float dt)
        {
            scene->GetCamera()->Shake(blastTime, 25, { 50.0f,100.0f });
            Next();
            return;
        }
    );

    QueueWaitEvent(blastTime);

    QueueFadeOutEvent(blastTime/2.0f);

    QueueDoneEvent();
}
