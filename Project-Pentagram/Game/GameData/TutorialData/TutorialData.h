#pragma once
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
public:
    TutorialType SelectedTutorial = TutorialType::TimelineTutorial;
};