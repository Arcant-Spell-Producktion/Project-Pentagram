#include "Game/GameData/CasterData/PlayerData.h"
#include "Game/GameData/MapData/MapData.h"
#include "Utilities/Singleton.h"

class RuntimeGameData : public Singleton<RuntimeGameData>
{
public:
    PlayerData* Player = nullptr;
    MapData* Map = nullptr;

    RuntimeGameData(PlayerData* player = nullptr, MapData* map = nullptr);

    PlayerData* GetPlayerData() { return Player; }

    ~RuntimeGameData()
    {
        delete Player;
        delete Map;
    }
};