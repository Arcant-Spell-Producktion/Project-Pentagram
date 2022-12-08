#include "Engine/IGameObjectManager.h"
class ScrollButton : public Button
{
private:
    const glm::vec3 DefaultScale = { 240.0f, 160.0f, 1.0f };
    const glm::vec3 ExpandScale = { 260.0f, 160.0f, 1.0f };;

public:
    ScrollButton(std::string text);
};