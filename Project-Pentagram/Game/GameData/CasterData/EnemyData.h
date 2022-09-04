
#include "CasterData.h"

class EnemyData : public CasterData
{
private:
    CasterPosition m_Position = CasterPosition::CasterB;

public:
    EnemyData(CasterData data) :
        CasterData(data)
    {
    }
};