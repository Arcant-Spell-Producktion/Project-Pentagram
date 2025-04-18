﻿#pragma once
#include "Game/GameData/MapData/NodeData.h"
#include "Game/GameData/CasterData/PlayerData.h"

#include <string>
#include <vector>

#include "TutorialEvent.h"
#include "Game/BattleScene/GameObject/MainObjectEnum.h"

enum class TutorialGoal
{
    Kill,
    Survive,
};


class TutorialNode : public NodeData
{
protected:
    TutorialEvents m_TutorialEvents;

    CasterData* m_TutorialPlayerData = nullptr;

    TutorialGoal m_TutorialGoal = TutorialGoal::Kill;
public:

    PentagramData_T PlayerStartSpell = {1,1,1,1,0};
    std::vector<PentagramData_T> TutorialSpells;

    std::string CompleteText = "Goodjob!";
    std::string RetryText = "Try Again!";

    int PlayerHP = 10;
    int EnemyHP = 10;


    int PlayerMana = 2;
    int PlayerManaWheel = 1;

    int EnemyMana = 3;

    TutorialNode(EnemyData enemy) : NodeData(enemy)
    {

    }

    TutorialEvents GetTutorialEvents() const
    {
        return m_TutorialEvents;
    }

    TutorialGoal GetTutorialGoal()
    {
        return m_TutorialGoal;
    }

    CasterData* GetPlayerData()
    {
        return m_TutorialPlayerData;
    }
};