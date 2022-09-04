#include "CasterData.h"

class PlayerData: public CasterData  
{
private:
    int m_Level;
    CasterPosition m_Position = CasterPosition::CasterA;
public:
    PlayerData(CasterData data,int level = 1) :
        CasterData(data),
        m_Level(level)
    {
    }
};