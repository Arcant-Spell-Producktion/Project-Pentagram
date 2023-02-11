#include "RuntimeGameData.h"

RuntimeGameData::RuntimeGameData(PlayerData* player, MapData* map)
{
    if (player) Player = new PlayerData(*player);
    if (map) Map = new MapData(*map);
}
