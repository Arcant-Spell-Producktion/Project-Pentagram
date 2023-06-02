#include "CreditCutScene.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/Slideshow/Slide/CreditSlide.h"


void CreditCutScene::FadeUpdate(const float& dt)
{
    if (m_IsFadeOut)
    {
        m_FadeScreen->color.a = m_FadeCurrentTime / m_FadeTime;
        m_FadeCurrentTime += dt;
        if (m_FadeCurrentTime >= m_FadeTime)
        {
            SceneManager::LoadScene(m_NextState);
        }
    }
}

void CreditCutScene::GameSceneLoad()
{

}

void CreditCutScene::GameSceneInit()
{
    // Set FadeScreen Component
    m_FadeScreen = CreateUIObject("fadeScreen");
    m_FadeScreen->scale = { 1920.0f, 1080.0f, 1.0f };
    m_FadeScreen->color = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_FadeScreen->SetActive(false);

    m_Slide = CreateObject((new CreditSlide())->Init());
    m_Slide->SlideDoneEvent.AddListener([this](bool isDone) { FadeOut(1.0f,GameState::GS_MENU_SCENE); });
    m_Slide->Play();
}

void CreditCutScene::GameSceneUpdate(float dt)
{
    GameScene::GameSceneUpdate(dt);
    FadeUpdate(dt);

    if (Input::IsKeyPressed(GLFW_KEY_ENTER))
    {
        m_Slide->SlideDoneEvent.Invoke(true);
    }
    else if (Input::IsKeyPressed(GLFW_KEY_R))
    {
        SceneManager::LoadScene(GameState::GS_RESTART);
        return;
    }

    // Update GameObject
    for (GLuint idx = 0; idx < objectsList.size(); idx++)
    {
        GameObject*& curObj = objectsList[idx];

        curObj->OnUpdate(dt);
        if (curObj->IsAnimationObject())
        {
            curObj->UpdateAnimation(dt);
        }
        if (curObj->GetTag() == GameObjectTag::PARTICLE && Input::IsKeyBeginPressed(GLFW_KEY_4))
        {
            curObj->SetActive(curObj->IsActive() ? false : true);
        }
    }
    // Update UI
    for (GLuint idx = 0; idx < uiObjectsList.size(); idx++)
    {
        UIObject*& curObj = uiObjectsList[idx];

        if (!curObj->IsActive()) { continue; }
        curObj->OnUpdate(dt);
    }
}

void CreditCutScene::GameSceneFree()
{
    GameScene::GameSceneFree();
}
