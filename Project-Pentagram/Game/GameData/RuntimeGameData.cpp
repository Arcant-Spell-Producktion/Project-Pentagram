#include "RuntimeGameData.h"
#include <fstream>
#include <iostream>
#include <array>

#include "CasterData/CasterStatDatabase.h"

void RuntimeGameData::DeleteSave()
{
    if (std::remove("save.dat") == 0)
    {
        std::cout << "Save file deleted successfully.\n";
    }
    else
    {
        std::cout << "Error deleting save file.\n";
    }
}

void RuntimeGameData::SaveGameData()
{
    PlayerSaveData playerData = Player->SavePlayerData();
    MapSaveData mapData = Map->SaveMapData();

    std::ofstream outputFile("save.dat");

    if (outputFile.is_open())
    {
        outputFile << playerData.element_index << " " << playerData.level << " " << playerData.hp << std::endl;

        // Save map data to file
        outputFile << mapData.completeChapter << " " << mapData.currentChapterElement << " ";
        for (int i = 0; i < mapData.nodeIndex.size(); i++)
        {
            outputFile << mapData.nodeIndex[i] << " ";
        }
        for (int i = 0; i < mapData.canVisit.size(); i++)
        {
            outputFile << mapData.canVisit[i] << " ";
        }
        outputFile << std::endl;

        outputFile.close();

        std::cout << "Game Saved!\n";
    }
    else
    {
        std::cout << "Unable to open file!\n";
    }
}

bool RuntimeGameData::LoadGameData()
{
    std::ifstream inputFile("save.dat");

    if (inputFile.is_open())
    {
        PlayerSaveData playerData;
        MapSaveData mapData;

        // Load player data from file
        inputFile >> playerData.element_index >> playerData.level >> playerData.hp;

        // Load map data from file
        inputFile >> mapData.completeChapter >> mapData.currentChapterElement;
        for (int i = 0; i < mapData.nodeIndex.size(); i++)
        {
            inputFile >> mapData.nodeIndex[i];
        }
        for (int i = 0; i < mapData.canVisit.size(); i++)
        {
            inputFile >> mapData.canVisit[i];
        }

        inputFile.close();

        Element::Type element = static_cast<Element::Type>(playerData.element_index);
        Player = new PlayerData({ CasterStatDatabase::GetInstance()->GetStat(
            element,CasterType::Player,playerData.level), element, CasterPosition::CasterA }, playerData.level);
        Player->Stat().CurrentHealth = playerData.hp;

        Map = new MapData(Player->Element());
        Map->LoadMapData(mapData);

        return true;
    }
    else
    {
        std::cout << "Unable to open file!\n";
    }

    return false;
}
