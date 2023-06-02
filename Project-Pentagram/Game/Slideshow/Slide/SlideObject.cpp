#include "SlideObject.h"

#include "Engine/GameStateController.h"

void SlideObject::Next()
{
    std::cout << "Next SLide!\n";
    UpdateCamera();
    m_TotalTime = 0.0f;
    if (m_SlideUpdateQueue.empty())
    {
        m_SlideState = SlideObjectState::Done;
        SlideDoneEvent.Invoke(true);
        return;
    }
    m_CurrentUpdateFunc = m_SlideUpdateQueue.front();
    m_SlideUpdateQueue.pop();
}

void SlideObject::UpdateCamera(float camX, float camY, float zoom)
{
    GameScene* scene = GameStateController::GetInstance().currentScene;
    Camera* camera = scene->GetCamera();

    camera->SetZoom(zoom);
    camera->position.x = camX;
    camera->position.y = camY;
}

void SlideObject::SetFadeScreen(float alpha)
{
    m_FadeScreen->color.a = alpha;
}

void SlideObject::ShowImage(int index, float alpha)
{
    m_Images[index]->color.a = alpha;
    m_Images[index]->SetActive(true);
}

void SlideObject::HideImage(int index)
{
    m_Images[index]->SetActive(false);
}

void SlideObject::ShowText(int index)
{
    m_Texts[index]->SetActive(true);
}

void SlideObject::HideText(int index)
{
    m_Texts[index]->SetActive(false);
}

void SlideObject::HideAll()
{
    m_PromptText->SetActive(false);
    for (GameObject* image : m_Images) image->SetActive(false);
    for (TextObject* text : m_Texts) text->SetActive(false);
}

void SlideObject::OnUpdate(const float& dt)
{
    if (m_SlideState == SlideObjectState::Init || m_SlideState == SlideObjectState::Done) return;
    if (m_CurrentUpdateFunc == nullptr) Next();

    m_TotalTime += dt;
    m_CurrentUpdateFunc(dt);
}

SlideObject::SlideObject() :UIObject("Slide")
{
    this->scale = { 1920.0f,1080.0f,1.0f };
    this->color = {0.0f,0.0f,0.0f,1.0f };

    m_SlideState = SlideObjectState::Init;
    m_CurrentUpdateFunc = nullptr;
    m_TotalTime = 0.0f;

    m_PromptText = new TextObject("CurrentText");
    m_PromptText->text = "Click to continue";
    m_PromptText->fontSize = 64;
    m_PromptText->textAlignment = TextAlignment::MID;
    m_PromptText->isVCenterAlignment = true;
    m_PromptText->position = { 600.0f,-480.0f,1.0f };
    m_PromptText->SetActive(false);

    m_FadeScreen = new UIObject("FadeScreen");
    m_FadeScreen->scale = { 1920.0f,1080.0f,1.0f };
    m_FadeScreen->color = { 0.0f,0.0f,0.0f,0.0f };

    m_ImageLayer = new UIObject("ImageLayer");
    m_ImageLayer->color.a = 0.0f;

    m_TextLayer = new UIObject("TextLayer");
    m_TextLayer->color.a = 0.0f;


    this->SetChildRenderFront(m_ImageLayer);
    this->SetChildRenderFront(m_TextLayer);
    this->SetChildRenderFront(m_PromptText);
    this->SetChildRenderFront(m_FadeScreen);
}

void SlideObject::QueueUpdateFunction(SlideUpdateFunc func)
{
	m_SlideUpdateQueue.push(func);
}

void SlideObject::QueueWaitClickEvent()
{
    m_SlideUpdateQueue.push([this](const float& dt)
        {
            if (Input::IsKeyBeginPressed(GLFW_MOUSE_BUTTON_LEFT))
            {
                HideAll();
                Next();
                return;
            }
            m_PromptText->SetActive(true);
        });
}

void SlideObject::QueueWaitEvent(float time)
{
    m_SlideUpdateQueue.push([this, time](const float& dt) 
        {
            if (m_TotalTime >= time) Next();
        });
}

void SlideObject::QueueTextEvent(std::vector<int> textIds)
{
    m_SlideUpdateQueue.push([this, textIds](const float& dt)
        {
            SetFadeScreen(0.0f);

            for (int id : textIds)
            {
                ShowText(id);
            };

            Next();
        });

}

void SlideObject::QueueFadeFromBlackEvent(std::vector<int> imageIds, float time, glm::vec3 CC)
{
    m_SlideUpdateQueue.push([this, imageIds, time](const float& dt)
        {
            HideAll();
            SetFadeScreen(1.0f);
            for (int id : imageIds) ShowImage(id);
            Next();
        });

    m_SlideUpdateQueue.push([this, imageIds, CC, time](const float& dt)
        {
            float progress = (m_TotalTime / time);
            float alpha = 1.0f - progress;

            UpdateCamera(CC.x*progress, CC.y*progress, 1 + CC.z * progress);

            SetFadeScreen(alpha);
            if (m_TotalTime >= time) Next();
        });
}

void SlideObject::QueueFadeInEvent(std::vector<int> imageIds, float alpha, float time)
{
    m_SlideUpdateQueue.push([this, imageIds, alpha, time](const float& dt)
        {
            float progress = (m_TotalTime / time);
            if (std::isinf(progress))
            {
                progress = 1.0f;
            }

            float a = alpha * progress;

            for (int id : imageIds) ShowImage(id, a);
            if (m_TotalTime >= time) Next();
        });
}

void SlideObject::QueueFadeOutEvent(std::vector<int> imageIds, float alpha, float time)
{
    m_SlideUpdateQueue.push([this, imageIds, alpha, time](const float& dt)
        {
            float progress = (m_TotalTime / time);
            if (std::isinf(progress))
            {
                progress = 1.0f;
            }

            float a = 1 - (alpha * progress);
            
            for (int id : imageIds) ShowImage(id, a);
            if (m_TotalTime >= time) Next();
        });
}

void SlideObject::QueueFadeToBlackEvent(float time, glm::vec3 CC)
{
    m_SlideUpdateQueue.push([this,time , CC](const float& dt)
        {
            float progress = (m_TotalTime / time);
            float alpha = progress;
            SetFadeScreen(alpha);

            UpdateCamera(CC.x * progress, CC.y * progress, 1 + CC.z * progress);

            if (m_TotalTime >= time)
            {
                HideAll();
                Next();
            }
        });
}

int SlideObject::AddTextObject(TextObject* text)
{
    text->SetActive(false);
    text->SetRenderTime(0.005f);

    int index = m_Texts.size();
    m_TextLayer->SetChildRenderBack(text);
    m_Texts.push_back(text);
    return index;
}

int SlideObject::AddImageObject(GameObject* image)
{
    image->SetActive(false);

    int index = m_Images.size();
    m_ImageLayer->SetChildRenderBack(image);
    m_Images.push_back(image);
    return index;
}

void SlideObject::Play()
{
    m_SlideState = SlideObjectState::Play;
    m_CurrentUpdateFunc = m_SlideUpdateQueue.front();
    m_SlideUpdateQueue.pop();
}

