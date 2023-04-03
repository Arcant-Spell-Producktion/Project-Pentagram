#include "TutorialData.h"

#include "TutorialNodes/TimeTutorialNode.h"

TutorialData::TutorialData()
{
    m_TutorialNodes[TutorialType::TimelineTutorial] = new TimeTutorialNode();
}

TutorialNode* TutorialData::GetTutorialNode()
{
    return m_TutorialNodes[SelectedTutorial];
}
