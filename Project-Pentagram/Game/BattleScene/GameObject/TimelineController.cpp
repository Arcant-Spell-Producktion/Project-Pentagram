#include "Engine/GameStateController.h"
#include "Game/BattleScene/BattleManager.h"
#include "TimelineController.h"

TimelineController::TimelineController():m_ObjectManager(GameStateController::GetInstance()->currentScene), UIObject("TimelineUI")
{
    this->color.a = 0.0f;
    this->position.y += 400.0f;

    top = new UIObject("Timeline_UI_Banner");
    top->scale = { 1320.0f,40.0f,1.0f };
    top->position.y += 120.0f;
    top->color.a = 0.0f;
    this->SetChildRenderFront(top);

    trackMarker = new UIObject("Timeline_Track_Marker");
    trackMarker->scale = { 40.0f,40.0f,1.0f };
    trackMarker->SetActive(false);
    trackMarker->SetTexture("Sprites/UI/Game/ui_game_spell-icon_border.png");
    trackMarker->SetSpriteByIndex(0, 2);
    top->SetChildRenderFront(trackMarker);


    box = new UIObject("TimelineUIBOX");
    box->scale = { 1920.0f, 140.0f, 1.0f };
    box->position = { 0.0f, 140.0f / 2.0f, 0.0f };
    box->SetTexture("Sprites/UI/Game/Timeline/ui_game_timeline_header.png");
    this->SetChildRenderBack(box);

    timelineExpander = new UIObject("TimelineExpander");
    timelineExpander->SetTexture("Sprites/UI/Game/Timeline/ui_game_timeline_banner-border.png");
    timelineExpander->position.y -= (165.0f + box->scale.y / 2.0f);
    timelineExpander->scale = { 1320.0f, 128.0f, 1.0f };
    timelineExpander->SetActive(false);
    box->SetChildRenderFront(timelineExpander);

    auto bm = BattleManager::GetInstance();
    for (size_t i = 0; i < 11; i++)
    {
        std::function<void(bool doExpand)> expandFunc = [this, i](bool doExpand) { SetExpandTimeline(i, doExpand); };
        auto track = new TimetrackUI(i, bm->Data.Timeline.GetTimetrack(i), expandFunc);
        m_Tracks.push_back(track);
        box->SetChildRenderFront(track);
    }
    

}

void TimelineController::SetTrackerActive(bool isActive)
{
    trackMarker->SetActive(isActive);
}

void TimelineController::SetTrackerPositionByIndex(int index)
{
    trackMarker->position.x = index * 120.0f - 600.0f;
}

void TimelineController::SetPentragramControllerReference(PentragramController* _pentragramControllerRef)
{
    pentragramControllerRef = _pentragramControllerRef;
}

void TimelineController::SetCurrentState(BattleState state)
{
    currentState = state;
}

void TimelineController::SetExpandTimeline(int index, bool doExpand)
{
    if (doExpand)
    {
        if (currentExpanderIndex != -1)
        {
            ClearTimelineExpander();
        }

        InsertTimetrackToExpander(index);

        m_Tracks[index]->RemoveAllIcon();
        timelineExpander->SetActive(true);
        pentragramControllerRef->SetActive(false);
    }
    else
    {
        ClearTimelineExpander();

        timelineExpander->SetActive(false);

        if (currentState == BattleState::CastState)
        {
            pentragramControllerRef->SetActive(true);
            pentragramControllerRef->ResetPentagramButtonField();
        }
    }

}

int TimeToIndex(int t)
{
    int i = t - 1;
    return i >= 10 ? 10 : i;
}

void TimelineController::UpdatePreviewIcon(CastSpellDetail* spell)
{
    std::set<int> timeIndexs;
    if (spell == nullptr)
    {
        for (size_t i = 0; i < 11; i++)
        {
            m_Tracks[i]->PreviewIcon(spell, false, false);
        }
        return;
    }

    switch (spell->OriginalSpell->GetChannelEffectType())
    {
    case ChannelEffectEnum::None:
        timeIndexs.insert(TimeToIndex(spell->SelectedTime));
        for (size_t i = 0; i < 11; i++)
        {
            m_Tracks[i]->PreviewIcon(spell, true, timeIndexs.contains(i));
        }
        break;
    case ChannelEffectEnum::Wait:
        timeIndexs.insert(TimeToIndex(spell->SelectedTime));
        timeIndexs.insert(TimeToIndex(spell->SelectedTime + spell->OriginalSpell->GetChannelTime()));
        for (size_t i = 0; i < 11; i++)
        {
            m_Tracks[i]->PreviewIcon(spell, !(i == *timeIndexs.begin()), timeIndexs.contains(i));
        }
        break;
    case ChannelEffectEnum::Active:
        for (int t = spell->SelectedTime; t <= spell->SelectedTime + spell->OriginalSpell->GetChannelTime(); t++)
        {
            timeIndexs.insert(TimeToIndex(t));
        }
        for (size_t i = 0; i < 11; i++)
        {
            m_Tracks[i]->PreviewIcon(spell, true, timeIndexs.contains(i));
        }
        break;
    }
}

void TimelineController::AddIconToTrack(int index, CastSpellDetail* spell)
{
    std::cout << "ADD ICON 2\n";
	m_Tracks[index]->AddIcon(spell);
}

void TimelineController::ClearTrack(int index)
{
    m_Tracks[index]->ClearTrack();
}

void TimelineController::UpdateAllTracks()
{
    for (TimetrackUI* track : m_Tracks)
    {
        track->UpdateTrack();
    }
}

void TimelineController::ClearAllTrack()
{
    for (TimetrackUI* track: m_Tracks)
    {
        track->ClearTrack();
    }

    for (auto icon : timelineExpander->GetChildList())
    {
        m_ObjectManager->DeleteObjectByPointer(icon);
        timelineExpander->RemoveChild(icon);
    }
    timelineExpander->SetActive(false);

    if(currentExpanderIndex != -1) { m_Tracks[currentExpanderIndex]->SetIsExpand(false); }
    currentExpanderIndex = -1;
}

void TimelineController::ClearTimelineExpander()
{
    if (currentExpanderIndex == -1) { return; }

    std::vector<GameObject*> SpellIconList = timelineExpander->GetFrontRenderChildList();
    for (int idx = 0; idx < SpellIconList.size(); idx++)
    {
        SpellIconUI* spellIcon = dynamic_cast<SpellIconUI*>(SpellIconList[idx]);
        timelineExpander->RemoveChild(spellIcon);
        spellIcon->position = { 0.0f, 0.0f, 0.0f };
        m_Tracks[currentExpanderIndex]->AddIcon(spellIcon);

        if (SpellIconList.size() - (idx + 1) > 0)
        {
            spellIcon->SetActive(false);
        }
    }
    m_Tracks[currentExpanderIndex]->SetIsExpand(false);
    currentExpanderIndex = -1;
}

void TimelineController::InsertTimetrackToExpander(int index)
{
    currentExpanderIndex = index;

    const float offset = 65.0f;
    const float gap = 15.0f;
    float initXPosition = -timelineExpander->scale.x / 2.0f;

    std::vector<SpellIconUI*> curSpellIconList = m_Tracks[index]->GetSpellDetailUIList();
    for (int idx = 0; idx < curSpellIconList.size(); idx++)
    {
        SpellIconUI* spellIcon = curSpellIconList[idx];

        spellIcon->parent->RemoveChild(spellIcon);
        timelineExpander->SetChildRenderFront(spellIcon);
        spellIcon->SetActive(true);
        spellIcon->SetIsExtra(false);
        spellIcon->position = { (idx * (spellIcon->scale.x + gap)) + initXPosition + offset, 0.0f, 0.0f};
    }
}