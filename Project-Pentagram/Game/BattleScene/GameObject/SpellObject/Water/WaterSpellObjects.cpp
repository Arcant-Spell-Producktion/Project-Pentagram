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
    float startX = (600.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-700.0f + size / 4) * m_SpellTarget; // Assume B recieve
    float yPos = -160.0f;
    this->scale = { -size * m_SpellTarget,size,1.0f };
    glm::vec3 startPos = { startX ,yPos,0.0f };
    glm::vec3 endPos = { endX ,yPos,0.0f };
    float travelTime = 1.5f;

    this->position = startPos;
    this->SetIsAnimationObject(true);

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void WaterSpell2::Initialize()
{
    float size = 320.0f;
    float startX = (540.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-640.0f + size / 4) * m_SpellTarget;
    float yPos = -size/2;
    this->scale = { size*2 * -m_SpellTarget ,size,1.0f };
    this->position = { startX,yPos,1.0f };
    this->SetIsAnimationObject(true);

    float timePerFrame = 0.1f;

    glm::vec3 startPos = { startX ,yPos,0.0f };
    glm::vec3 endPos = { endX ,yPos,0.0f };
    float travelTime = 1.5f;


    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent(true);
    QueueWaitEvent(timePerFrame);
    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();
    QueueDoneEvent();
}

void WaterSpell3::Initialize()
{
    float size = 640.0f;
    float xPos = (-700.0f) * m_SpellTarget; // Assume A shooter
    float yPos = 0.0f;
    this->scale = { size / 2 ,size,1.0f };
    this->position = { xPos ,yPos,1.0f };
    this->SetIsAnimationObject(true);

    float timePerFrame = 0.15f;


    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent();

    QueueHitEvent();

    QueueDoneEvent();

}

void WaterSpell4::Initialize()
{
    std::cout << "Rebound Wave::Init\n";
    x_index = 0;
    float size = 640.0f;
    float yPos = -160.0f;
    this->scale = { size * -m_SpellTarget  ,size / 2,1.0f };
    this->position = { x_Positions[x_index] * m_SpellTarget,yPos,1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(true);
    
    float timePerFrame = 0.15f;


    this->SetAnimationPlayTime(timePerFrame);

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
                    auto scene = GameStateController::GetInstance()->currentScene;
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
    float xPos = (700.0f) * m_SpellTarget; // Assume A shooter
    float yPos = -160.0f;
    this->scale = { size*2 ,size,1.0f };
    this->position = { xPos,yPos,1.0f };
    this->SetIsAnimationObject(true);
    this->SetIsAnimationLoop(false);

    float timePerFrame = 0.15f;

    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent(true);
    
    QueueHitEvent();

    QueueWaitTillFrameEvent();

    QueueDoneEvent();

}

void WaterSpell6::Initialize()
{
    std::cout << "Water Beam::Init\n";
    float size = 480.0f;
    float xPos = (800.0f) * m_SpellTarget; // Assume A shooter
    float yPos = 0.0f;
    this->scale = { size ,size,1.0f };
    this->position = { xPos,yPos,1.0f };
    this->color.a = 0.0f;
    this->SetIsAnimationObject(false);

    auto scene = GameStateController::GetInstance()->currentScene;
    for (size_t i = 0; i < 4; i++)
    {
        auto _section = scene->CreateGameObject("WaterBeam"+i);

        _section->scale = { size * -m_SpellTarget ,size,1.0f };
        _section->position.x = size * i * -m_SpellTarget;
        _section->SetTexture(this->m_TexturePath);
        _section->SetSpriteByIndex(i, 0);
        _section->SetIsAnimationObject(true);

        this->SetChildRenderFront(_section);
        m_Section.push_back(_section);
    }
    float timePerFrame = 0.1f;
    this->SetAnimationPlayTime(timePerFrame);

    QueueUpdateFunction(
        [this](float dt)
        {
            if (m_Section[3]->GetCurrentAnimationColumn() == 7)
            {
                for (size_t i = 0; i < 4; i++)
                {
                    m_Section[i]->SetSpriteByIndex(i + 4, 0,true);
                }
                Next();
                return; 
            }
        }
    );

    QueueHitEvent();

    QueueWaitEvent(3.0f);

    QueueDoneEvent();

}

void WaterSpell7::Initialize()
{
    float size = 320.0f;
    float startX = (540.0f) * m_SpellTarget; // Assume A shooter
    float endX = (-640.0f + size / 4) * m_SpellTarget;
    float yPos = -size / 2;
    this->scale = { size * 2 * -m_SpellTarget ,size ,1.0f };
    this->position = { startX,yPos,1.0f };
    this->SetIsAnimationObject(true);


    glm::vec3 startPos = { startX ,yPos,0.0f };
    glm::vec3 endPos = { endX ,yPos,0.0f };
    float travelTime = 1.5f;


    float timePerFrame = 0.15f;
    this->SetAnimationPlayTime(timePerFrame);

    QueueWaitTillFrameEvent(true);

    QueueMoveEvent(startPos, endPos, travelTime);

    QueueHitEvent();

    QueueDoneEvent();
}

void WaterSpell8::Initialize()
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

void WaterSpell9::Initialize()
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
