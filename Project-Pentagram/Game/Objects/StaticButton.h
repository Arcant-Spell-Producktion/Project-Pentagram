#pragma once

#include "Engine/IGameObjectManager.h"
class StaticButton : public Button
{
public:
    StaticButton(std::string text, const glm::vec3& scale = { 350.0f, 90.0f, 1.0f });
};