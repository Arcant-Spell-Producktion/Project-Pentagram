#include <array>
#include <vector>
#include "Game/BattleScene/SpellCaster/CastSpellDetail.h"

class SpellTimeline 
{
private:
    array<vector<CastSpellDetail*>, 11> m_Timelines;

public:
    void AddSpellToTimeline(CastSpellDetail* spell)
    {
        int array_index = spell->SelectedTime <= 10 ? (spell->SelectedTime - 1) : (11 - 1);
        m_Timelines[array_index].push_back(spell);
    }
};