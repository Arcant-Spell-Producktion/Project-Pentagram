#pragma once
#include "Engine/IGameObjectManager.h"
class ScrollButton : public Button
{
private:
    const glm::vec3 DefaultScale = { 240.0f, 160.0f, 1.0f };
    const glm::vec3 ExpandScale = { 260.0f, 160.0f, 1.0f };

    bool m_isExpand = false;
    bool m_isToggle = false;
public:
    ScrollButton(std::string text, const glm::vec3& _DefaultScale = { 240.0f, 160.0f, 1.0f }, const glm::vec3& _ExpandScale = { 260.0f, 160.0f, 1.0f });

    void SetToggleButton(bool isToggle);
    void SetExpand(bool isExpand);
};