#include "FireballObject.h"

void FireballObject::Initialize()
{
    std::cout << "Fireball::Init\n";
    float speed = 10.0f;
    float startX = (-700.0f + 160.0f + 80.0f) * m_SpellTarget;
    this->scale = { 160.0f,160.0f,1.0f };
    glm::vec3 startPos = { startX ,-150.0f,0.0f };
    glm::vec3 endPos = { -startX ,-150.0f,0.0f };

    this->position = startPos;

    //Move A to B
    glm::vec3 direction = endPos - startPos;
    float travelTime = 1.0f;

    QueueUpdateFunction(
        [this, direction, travelTime](float dt)
        {
            std::cout << "\tSpell::Move\n";
            if (m_TotalTime >= travelTime)
            {
                Next();
                return;
            }
            float progress = m_TotalTime / travelTime;

            this->position.x = direction.x * progress;
            this->position.y = direction.x * progress;
        }
    );

    QueueHitEvent();
    QueueDoneEvent();
}
