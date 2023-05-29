#include "OpeningCutScene.h"

SlideObject* OpeningCutScene::Init()
{

#pragma region Init
    std::string SceneAText = R"(There was a world where the 4 magic nations once
peacefully co-existing alongside each other with the help of
the guardian witch of each nation.

But, one day cult of the old ones decides to awaken the
ancient horror to grant them the power to take down those
witches and rule over all the land.)";

    std::string SceneBText = R"(Only one persists  with the strongest WILL among the 4
gradian witch, she's able to resist the corruption from the
ancient entity.

Now she is the last hope to stop the force of corruption
from taking over the entire world and save other witches
before it's too late.)";

    TextObject* textA = new TextObject("SceneAText");
    textA->text = SceneAText;
    textA->fontSize = 64;
    textA->textAlignment = TextAlignment::MID;
    textA->isVCenterAlignment = true;

    TextObject* textB = new TextObject("SceneBText");
    textB->text = SceneBText;
    textB->fontSize = 64;
    textB->textAlignment = TextAlignment::MID;
    textB->isVCenterAlignment = true;

    GameObject* MapObj = new GameObject("Map");
    MapObj->scale = { 1920.0f,1080.0f,1.0f };
    MapObj->SetTexture("Sprites/Map/world_map.png");

    GameObject* BossA = new GameObject("BossA");
    BossA->scale = { 1920.0f,1080.0f,1.0f };
    BossA->SetTexture("Sprites/CutScene/Cutscene_begining_appear.png");
    BossA->SetIsAnimationObject(true);

    GameObject* FogA = new GameObject("FogA");
    FogA->scale = { 1920.0f,1080.0f,1.0f };
    FogA->SetTexture("Sprites/Map/map_fog_Earth.png");
    GameObject* FogB = new GameObject("FogA");
    FogB->scale = { 1920.0f,1080.0f,1.0f };
    FogB->SetTexture("Sprites/Map/map_fog_Fire.png");
    GameObject* FogC = new GameObject("FogA");
    FogC->scale = { 1920.0f,1080.0f,1.0f };
    FogC->SetTexture("Sprites/Map/map_fog_Water.png");
    GameObject* FogD = new GameObject("FogA");
    FogD->scale = { 1920.0f,1080.0f,1.0f };
    FogD->SetTexture("Sprites/Map/map_fog_Wind.png");

#pragma endregion

    int _TextA = AddTextObject(textA);
    int _TextB = AddTextObject(textB);
    int _BossA = AddImageObject(BossA);
    int _Map = AddImageObject(MapObj);
    int _FogA = AddImageObject(FogA);
    int _FogB = AddImageObject(FogB);
    int _FogC = AddImageObject(FogC);
    int _FogD = AddImageObject(FogD);

    QueueTextEvent({ _TextA });
    QueueWaitEvent(2.0f);
    QueueWaitClickEvent();

    QueueFadeFromBlackEvent({_Map});
    QueueWaitEvent();
    QueueFadeToBlackEvent(3.0f,{5.0f,45.0f,2.0f});

    QueueFadeFromBlackEvent({ _BossA });
    QueueWaitEvent();
    QueueUpdateFunction(
        [this, _BossA](const float& dt)
        {
            m_Images[_BossA]->SetTexture("Sprites/CutScene/Cutscene_begining_fog.png");
            Next();
        });
    QueueWaitEvent(1.0f);
    QueueFadeToBlackEvent();

    QueueFadeFromBlackEvent({ _Map,_FogA,_FogB,_FogC,_FogD }, 2.0f);
    QueueWaitEvent();
    QueueFadeOutEvent({ _FogA,_FogB,_FogC,_FogD }, 0.3f, 3.0f);
    QueueWaitEvent(2.0f);
    QueueFadeToBlackEvent();

    QueueTextEvent({ _TextB });
    QueueWaitEvent(2.0f);
    QueueWaitClickEvent();

    std::cout << "INITT INTOR CUNTSCACA\n";

    return this;
}
