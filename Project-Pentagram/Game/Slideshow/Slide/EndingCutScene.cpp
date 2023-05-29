#include "EndingCutScene.h"

#include "Game/GameData/RuntimeGameData.h"

SlideObject* EndingCutScene::Init()
{
    RuntimeGameData& gameData = RuntimeGameData::GetInstance();
    bool IsChapterComplete[4] = { false,false,false,false };
    
    std::vector <GameObject*> PanelA;
    std::vector <GameObject*> Map;

    std::vector <int> _PanelA;
    std::vector <int> _Map;

    bool IsAllChapterComplete = true;
    for (bool isComplete : IsChapterComplete)
    {
        if (!isComplete)
        {
            IsAllChapterComplete = false;
            break;
        }
    }

#pragma region Init

    const std::string CasterSpritePath[3][4] =
    {
        {
            "Sprites/Character/Player/character_player_earth.png",
            "Sprites/Character/Player/character_player_fire.png",
            "Sprites/Character/Player/character_player_water.png",
            "Sprites/Character/Player/character_player_wind.png"
        },
        {
            "Sprites/Character/Boss/character_boss_earth.png",
            "Sprites/Character/Boss/character_boss_fire.png",
            "Sprites/Character/Boss/character_boss_water.png",
            "Sprites/Character/Boss/character_boss_wind.png"
        },
        {
            "Sprites/CutScene/Cutscene_final_earth-witch.png",
            "Sprites/CutScene/Cutscene_final_fire-witch.png",
            "Sprites/CutScene/Cutscene_final_water-witch.png",
            "Sprites/CutScene/Cutscene_final_wind-witch.png"
        }
    };

    const std::string FogPath[4] =
    {
        "Sprites/Map/map_fog_Earth.png",
        "Sprites/Map/map_fog_Fire.png",
        "Sprites/Map/map_fog_Water.png",
        "Sprites/Map/map_fog_Wind.png"
    };

    const glm::vec3 witchPosition[4] = {
        {523.0f, 10.0f, 0.0f},
        { -456.0f, 95.0f, 0.0f },
       { 232.0f, 390.0f, 0.0f },
        { -172.0f, -210.0f, 0.0f }
    };

    for (int i = 0; i < 4; i++)
    {
        Element::Type element = static_cast<Element::Type>(i);
        if (element == (gameData.Player->Element()) || gameData.Map->IsChapterComplete(element))
        {
            IsChapterComplete[i] = true;
        }
    }

    std::string SceneAText = R"(The ancient entity has been defeated by the witch and all
the other guardian witches was saved from being
corrupted by the ancient entity's power.

Peace has returned to the world of magic once more
because all of the people that lived in it are at peace
knowing that they are protected from the hand of the
evil cult and their God by the guardian witches)";

    std::string SceneBText = R"(The ancient entity has been defeated by the witch and all
the other guardian witches was saved from being
corrupted by the ancient entity's power.

Peace has returned to some regions,but the guardians still
need to purge the land of the lingering corruptions left by
the ancient entity fragment.)";

    TextObject* textA = new TextObject("SceneAText");
    textA->text = IsAllChapterComplete ? SceneAText : SceneBText;
    textA->fontSize = 64;
    textA->textAlignment = TextAlignment::MID;
    textA->isVCenterAlignment = true;

    GameObject* BossA = new GameObject("BossA");
    BossA->scale = { 1920.0f,1080.0f,1.0f };
    BossA->SetTexture("Sprites/CutScene/Cutscene_final_hit.png");

    GameObject* MapObj = new GameObject("Map");
    MapObj->scale = { 1920.0f,1080.0f,1.0f };
    MapObj->SetTexture("Sprites/Map/world_map.png");
    Map.push_back(MapObj);

    for (int i = 3; i >= 0; i--)
    {
        GameObject* mapWitch = new GameObject("MapWitch" + std::to_string(i));
        mapWitch->position = witchPosition[i];
        mapWitch->scale = { 200.0f,200.0f,1.0f };
        mapWitch->SetIsAnimationObject(true);
        mapWitch->SetIsAnimationLoop(true);

        if (IsChapterComplete[i])
        {
            GameObject* panelWitch = new GameObject("PanelAWitch"+ std::to_string(i));
            panelWitch->scale = { 1920.0f,1080.0f,1.0f };
            panelWitch->SetTexture(CasterSpritePath[2][i]);

            PanelA.push_back(panelWitch);

            
            mapWitch->SetTexture(CasterSpritePath[0][i]);
        }
        else
        {
            GameObject* tempFog = new GameObject("Fog");
            tempFog->scale = { 1920.0f,1080.0f,1.0f };
            tempFog->SetTexture(FogPath[i]);
            Map.push_back(tempFog);

            mapWitch->SetTexture(CasterSpritePath[1][i]);
        }

        Map.push_back(mapWitch);
    }

    GameObject* BossB = new GameObject("BossB");
    BossB->scale = { 1920.0f,1080.0f,1.0f };
    BossB->SetTexture("Sprites/CutScene/Cutscene_final_crack.png");

    GameObject* BossC = new GameObject("BossC");
    BossC->scale = { 1920.0f,1080.0f,1.0f };
    BossC->SetTexture("Sprites/CutScene/Cutscene_final_explode.png");
#pragma endregion

    _PanelA.push_back(AddImageObject(BossA));

    int _TextA = AddTextObject(textA);
    int _PanelB = AddImageObject(BossB);
    int _PanelC = AddImageObject(BossC);

    for (GameObject* obj : PanelA)
    {
        _PanelA.push_back(AddImageObject(obj));
    }

    for (GameObject* obj : Map)
    {
        _Map.push_back(AddImageObject(obj));
    }

    QueueFadeFromBlackEvent(_PanelA);
    QueueWaitEvent(2.0f);
    QueueFadeInEvent({ _PanelB });
    QueueWaitEvent(2.0f);
    QueueFadeInEvent({ _PanelC });
    QueueWaitEvent(2.0f);
    QueueFadeToBlackEvent();

    QueueTextEvent({ _TextA });
    QueueWaitEvent(3.0f);
    QueueWaitClickEvent();

    QueueFadeFromBlackEvent( _Map);
    QueueWaitEvent(2.0f);
    QueueFadeToBlackEvent();

    std::cout << "INITT INTOR CUNTSCACA\n";

    return this;
}
