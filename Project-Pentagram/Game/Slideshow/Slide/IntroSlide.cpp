#include "IntroSlide.h"

SlideObject* IntroSlide::Init()
{
    std::vector <GameObject*> Fog;
    std::vector <int> _Fog;

#pragma region Init

    const std::string FogPath[4] =
    {
        "Sprites/Map/map_fog_Earth.png",
        "Sprites/Map/map_fog_Fire.png",
        "Sprites/Map/map_fog_Water.png",
        "Sprites/Map/map_fog_Wind.png"
    };

    

    std::string SceneAText = R"(There was a world where the 4 magic nations once
peacefully co-existing alongside each other with the help of
the guardian witch of each nation.

But, one day cult of the old ones decides to awaken the
ancient horror to grant them the power to take down those
witches and rule over all the land.)";

    std::string SceneBText = R"(Only one persists  with the strongest WILL among the 4
guardian witch, she's able to resist the corruption from the
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

    for (int i = 0; i < 4; i++)
    {
       Fog.push_back(new GameObject("Fog"));
        Fog[i]->scale = { 1920.0f,1080.0f,1.0f };
        Fog[i]->SetTexture(FogPath[i]);
    }

#pragma endregion

    int _TextA = AddTextObject(textA);
    int _TextB = AddTextObject(textB);
    int _BossA = AddImageObject(BossA);
    int _Map = AddImageObject(MapObj);

    for (GameObject* obj : Fog)
    {
        _Fog.push_back(AddImageObject(obj));
    }

    QueueTextEvent({ _TextA });
    QueueWaitEvent(3.0f);
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

    std::vector <int> _MapNFog = _Fog;
    _MapNFog.push_back(_Map);

    QueueFadeFromBlackEvent(_MapNFog, 2.0f);
    QueueWaitEvent();
    QueueFadeOutEvent(_Fog, 0.3f, 3.0f);
    QueueWaitEvent(2.0f);
    QueueFadeToBlackEvent();

    QueueTextEvent({ _TextB });
    QueueWaitEvent(3.0f);
    QueueWaitClickEvent();

    std::cout << "INITT INTOR CUNTSCACA\n";

    return this;
}
