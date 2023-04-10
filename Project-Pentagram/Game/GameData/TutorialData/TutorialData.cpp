#include "TutorialData.h"

#include "TutorialNodes/CompareTutorialNode.h"
#include "TutorialNodes/TimeTutorialNode.h"

TutorialData::TutorialData()
{
    m_TutorialNodes[TutorialType::TimelineTutorial] = new TimeTutorialNode();
    m_TutorialNodes[TutorialType::WillCompareTutorial] = new CompareTutorialNode();

}

TutorialNode* TutorialData::GetTutorialNode()
{
    return m_TutorialNodes[SelectedTutorial];
}
