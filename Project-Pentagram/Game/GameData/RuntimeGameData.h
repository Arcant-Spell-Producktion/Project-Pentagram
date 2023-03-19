#include "Game/GameData/CasterData/PlayerData.h"
#include "Game/GameData/MapData/MapData.h"
#include "Utilities/Singleton.h"


class RuntimeGameData : public Singleton<RuntimeGameData>
{
public:
    PlayerData* Player = nullptr;
    MapData* Map = nullptr;

    RuntimeGameData(){};

    void DeleteSave();

    void SaveGameData();

    bool LoadGameData();

    void ClearGameData()
    {
        delete Player;
        delete Map;
    }

    ~RuntimeGameData()
    {
        ClearGameData();
    }
};

