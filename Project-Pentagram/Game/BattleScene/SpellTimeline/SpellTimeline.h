#include <array>
#include "SpellTimetrack.h"
#include <Game/BattleScene/GameObject/TimelineController.h>

class SpellTimeline 
{
private:
    array<SpellTimetrack, 11> m_Timeline;

public:
    TimelineController* UI;

    SpellTimetrack* GetTimetrack(int track_index) { return &m_Timeline[track_index]; }
    
    void AddSpellToTimeline(CastSpellDetail* spell,bool doCompare = true)
    {
        int array_index = spell->SelectedTime <= 10 ? (spell->SelectedTime - 1) : (11 - 1);
        m_Timeline[array_index].push_back(spell, doCompare);

        std::cout << "ADD ICON 1\n";
        UI->AddIconToTrack(array_index, spell);

        cout << "Add Spell to Timetrack index: " << array_index << "\n";
    }

    void UpdateTimeline()
    {
        UI->UpdateAllTracks();
    }

    void CompleteTimeline()
    {
        ResetTimeline();
        auto spellList = m_Timeline[10].GetSpellList();
        m_Timeline[10].clear(false);
        for (CastSpellDetail* csd: spellList)
        {
            csd->SelectedTime -= 10;
            AddSpellToTimeline(csd);
        }
    }

    void ResetTimeline(bool isHardClear = false)
    {
        int count = 10;

        if (isHardClear)count++;

        for (int i = 0; i < count; i++)
        {
            m_Timeline[i].clear();
        }

        UI->ClearAllTrack();
    }
};