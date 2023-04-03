#pragma once
#include "Game/GameData/MapData/NodeData.h"
#include "Game/GameData/CasterData/PlayerData.h"

#include <string>
#include <vector>

enum class TutorialGoal
{
    Kill,
    Survive,
};

class TutorialNode : public NodeData
{
protected:
    std::vector<std::string> m_TutorialText;

    CasterData* m_TutorialPlayerData = nullptr;

    TutorialGoal m_TutorialGoal = TutorialGoal::Kill;
public:
    TutorialNode(EnemyData enemy) : NodeData(enemy)
    {

    }

    std::string GetText(int i)
    {
        return m_TutorialText[i];
    }

    std::vector<std::string> GetTexts()
    {
        return m_TutorialText;
    };


    int GetTextCount() const
    {
        return m_TutorialText.size();
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