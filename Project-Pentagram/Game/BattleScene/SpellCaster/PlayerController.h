#include "CasterController.h"

class PlayerController : public CasterController
{
public:
    PlayerController(CasterData caster, void (*Update_func)(float) = nullptr) :
        CasterController(caster)
        {
        CasterController::m_CasterUpdate = Update_func;
        }
};