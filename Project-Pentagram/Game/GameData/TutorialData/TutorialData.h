#pragma once
#include <map>
#include <array>
#include <string>
#include "TutorialNodes/TutorialNode.h"



enum class TutorialType
{
    WillTutorial = 0,
    EffectTutorial,
    TimelineTutorial,
    WillCompareTutorial,
    WaitTutorial,
    ActiveTutorial,
    TrapTutorial,
    CounterTutorial,
};

class TutorialData
{
protected:
    static const std::string  m_TutorialNames[];
    std::map<TutorialType, TutorialNode* > m_TutorialNodes;
public:
    static std::string GetTutorialName(TutorialType type)
    {
        return m_TutorialNames[static_cast<int>(type)];
    }

    TutorialType SelectedTutorial = TutorialType::TimelineTutorial;

    TutorialData();

    TutorialNode* GetTutorialNode();
};
