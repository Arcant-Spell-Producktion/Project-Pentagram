#include "Engine/GameObject.h"
#include "Game/GameData/CasterData/CasterPosition.h"
#include "Game/Spells/SpellEffectType.h"

enum EffectObjectPlayMode
{
    Idle,
    Once,
    Freeze,
    Loop,
};

class BaseEffectObject : public GameObject
{
private:
    int m_Row = 0;
protected:
    bool isPlaying = false;
    EffectObjectPlayMode m_PlayMode;
    SpellEffectEnum m_Type;

public:
    BaseEffectObject(SpellEffectEnum effect);

    void Play();
    void Stop();

    void OnUpdate(const float& dt) override;
};