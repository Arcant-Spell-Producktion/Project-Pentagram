#include "TutorialData.h"

#include "TutorialNodes/ActiveTutorialNode.h"
#include "TutorialNodes/WillTutorialNode.h"
#include "TutorialNodes/EffectTutorialNode.h"
#include "TutorialNodes/CompareTutorialNode.h"
#include "TutorialNodes/CounterTutorialNode.h"
#include "TutorialNodes/TimeTutorialNode.h"
#include "TutorialNodes/TrapTutorialNode.h"
#include "TutorialNodes/WaitTutorialNode.h"

const std::string TutorialData::m_TutorialNames[] =
{
    "Part 1\nWill",
    "Part 2\nEffect",
    "Part 3\nTimeline",
    "Part 4\nSpell\nClashing",
    "Part 5\nChanneling\nSpell: Wait",
    "Part 6\nChanneling\nSpell: Active",
    "Part 7\nChanneling\nSpell: Trap",
    "Part 8\nChanneling\nSpell: Counter"
};

TutorialData::TutorialData()
{
    m_TutorialNodes[TutorialType::WillTutorial] = new WillTutorialNode();
    m_TutorialNodes[TutorialType::EffectTutorial] = new EffectTutorialNode();
    m_TutorialNodes[TutorialType::TimelineTutorial] = new TimeTutorialNode();
    m_TutorialNodes[TutorialType::WillCompareTutorial] = new CompareTutorialNode();
    m_TutorialNodes[TutorialType::WaitTutorial] = new WaitTutorialNode();
    m_TutorialNodes[TutorialType::ActiveTutorial] = new ActiveTutorialNode();
    m_TutorialNodes[TutorialType::TrapTutorial] = new TrapTutorialNode();
    m_TutorialNodes[TutorialType::CounterTutorial] = new CounterTutorialNode();
}

TutorialNode* TutorialData::GetTutorialNode()
{
    return m_TutorialNodes[SelectedTutorial];
}
