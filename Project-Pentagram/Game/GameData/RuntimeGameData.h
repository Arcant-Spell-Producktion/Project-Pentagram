#include "Game/GameData/CasterData/PlayerData.h"
#include "Game/GameData/MapData/MapData.h"
#include "TutorialData/TutorialData.h"
#include "Utilities/Singleton.h"


class RuntimeGameData : public Singleton<RuntimeGameData>
{
public:
    PlayerData* Player = nullptr;
    MapData* Map = nullptr;
    TutorialData Tutorial;

    RuntimeGameData(){};

    void SetPlayer(PlayerData* player)
    {
        if (player != nullptr)
        {
            delete Player;
            Player = nullptr;
        }

        Player = player;
    }

    void DeleteSave();

    void SaveGameData();

    bool LoadGameData();

    bool HaveSaveData();

    void ClearGameData()
    {
        delete Player;
        delete Map;

        Player = nullptr;
        Map = nullptr;
    }

    ~RuntimeGameData()
    {
        ClearGameData();
    }
};

