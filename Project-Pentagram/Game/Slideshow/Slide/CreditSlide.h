#pragma once

#include "SlideObject.h"

class CreditSlide :public SlideObject
{
private:
    void QueueMoveEvent(std::vector<int> imageIds, glm::vec3 startPos, glm::vec3 endPos, float travelTime);

    void QueueWaitTillFrameEvent(int id, bool doNextRow = false, bool waitLastFrame = true, int targetFrame = -1);
public:
    SlideObject* Init() override;
};

