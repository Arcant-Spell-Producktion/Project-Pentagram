#pragma once
#include <string>
#include <vector>

#include "Game/BattleScene/GameObject/MainObjectEnum.h"

struct TutorialObjectEvent
{
    MainObjectEnum Obj;
    bool Active;
};

class TutorialEvent
{
public:

    std::string TutorialText = "";
    std::vector<TutorialObjectEvent> ObjectEvents;

    TutorialEvent(std::string text) :TutorialText(text)
    {}
};

class TutorialEvents
{
private:
    std::vector<TutorialEvent> m_TutorialEvents;

public:

    int size() const
    {
        return m_TutorialEvents.size();
    }

    TutorialEvent& operator[](int i)
    {
        return m_TutorialEvents[i];
    }

    void AddStep(std::string text)
    {
        m_TutorialEvents.push_back(text);
    }

    void AddEvent(TutorialObjectEvent e)
    {
        m_TutorialEvents.back().ObjectEvents.push_back(e);
    }
};