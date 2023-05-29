#pragma once
#include <queue>
#include <vector>
#include "Engine/IGameObjectManager.h"
#include "Game/Objects/ScrollButton.h"



enum class SlideObjectState
{
    Init = 0,
    Play,
    Done
};

class SlideObject : public UIObject
{
private:
    typedef std::function<void(float)> SlideUpdateFunc;
    SlideUpdateFunc  m_CurrentUpdateFunc = nullptr;
    std::queue<SlideUpdateFunc> m_SlideUpdateQueue;

    TextObject* m_PromptText = nullptr;

    UIObject* m_FadeScreen = nullptr;

    UIObject* m_TextLayer = nullptr;
    GameObject* m_ImageLayer = nullptr;

protected:
    std::vector<TextObject*> m_Texts;
    std::vector<GameObject*> m_Images;

    SlideObjectState m_SlideState = SlideObjectState::Init;
    float m_TotalTime = 0.0f;

    void OnUpdate(const float& dt) override;

    virtual SlideObject* Init() = 0;
public:
    Event<bool> SlideDoneEvent;

    int AddTextObject(TextObject* text);
    int AddImageObject(GameObject* image);

    void Play();

    void Next();

    void UpdateCamera(float camX = 0.0f, float camY = 0.0f, float zoom = 1.0f);

    void SetFadeScreen(float alpha = 0.0f);

    void ShowImage(int index, float alpha = 1.0);

    void HideImage(int index);

    void ShowText(int index);

    void HideText(int index);

    void HideAll();

    SlideObject();

    void QueueUpdateFunction(SlideUpdateFunc func);

    void QueueWaitClickEvent();

    void QueueWaitEvent(float time = 1.0f);

    void QueueTextEvent(std::vector<int> textIds);

    void QueueFadeFromBlackEvent(std::vector<int> imageIds, float time = 2.0f, glm::vec3 CC = {0.0f,0.0f,0.0f});

    void QueueFadeInEvent(std::vector<int> imageIds, float alpha = 1.0f, float time = 2.0f);

    void QueueFadeOutEvent(std::vector<int> imageIds, float alpha = 1.0f, float time = 2.0f);

    void QueueFadeToBlackEvent(float time = 2.0f, glm::vec3 CC = { 0.0f,0.0f,0.0f });


};

