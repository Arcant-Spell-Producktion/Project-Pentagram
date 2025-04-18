#include "CasterController.h"

class PlayerController : public CasterController
{
public:
    void CasterDied() override;

    PlayerController(CasterData caster);

};