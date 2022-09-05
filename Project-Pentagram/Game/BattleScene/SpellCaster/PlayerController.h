#include "CasterController.h"

class PlayerController : public CasterController
{
public:
    PlayerController(CasterData caster) : CasterController(caster){}
};