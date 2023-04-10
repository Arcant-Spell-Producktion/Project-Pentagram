#pragma once
#include <map>
#include "TutorialNodes/TutorialNode.h"

enum class TutorialType
{
    PentagramTutorial = 0,
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
    std::map<TutorialType, TutorialNode* > m_TutorialNodes;
public:
    TutorialType SelectedTutorial = TutorialType::TimelineTutorial;

    TutorialData();

    TutorialNode* GetTutorialNode();
};
