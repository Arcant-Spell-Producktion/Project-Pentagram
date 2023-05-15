#include <string>
#include "CasterObject.h"
#include "Game/GameData/CasterData/CasterType.h"

const std::string CasterSpritePath[3][4] =
{
    {
        "Sprites/Character/Player/character_player_earth.png",
        "Sprites/Character/Player/character_player_fire.png",
        "Sprites/Character/Player/character_player_water.png",
        "Sprites/Character/Player/character_player_wind.png"
    },
    {
        "Sprites/Character/Minion/character_minion_earth.png",
        "Sprites/Character/Minion/character_minion_fire.png",
        "Sprites/Character/Minion/character_minion_water.png",
        "Sprites/Character/Minion/character_minion_wind.png"
    },
    {
        "Sprites/Character/Boss/character_boss_earth.png",
        "Sprites/Character/Boss/character_boss_fire.png",
        "Sprites/Character/Boss/character_boss_water.png",
        "Sprites/Character/Boss/character_boss_wind.png"
    }
};

const std::string CorruptSpritePath = "Sprites/Character/Boss/character_boss_corrupt.png";

void CasterObject::SetState(CasterObjectState state)
{
    SetState(state, state);
}

void CasterObject::SetState(CasterObjectState state, CasterObjectState nextState)
{
    m_State = state;
    m_NextState = nextState;

    SetSpriteByIndex(m_CasterType != CasterType::BigBoss ? (int)m_State : (int)m_CasterElement, 0);

    SetAnimationPlayTime(0.1f);
}

CasterObject::CasterObject(): GameObject("CasterObject")
{
    std::cout << "CREATE CASTER\n";

    this->SetIsAnimationObject(true);
    this->scale = { 320.0f, 320.0f, 1.0f };

    for(int i = static_cast<int>(SpellEffectEnum::Mark); i <= static_cast<int>(SpellEffectEnum::Boost); i++)
    {
        SpellEffectEnum eff = static_cast<SpellEffectEnum>(i);
        BaseEffectObject* effObj = new BaseEffectObject(eff);
        m_Effects[eff] = effObj;
        if ((eff == SpellEffectEnum::Overflow) || (eff == SpellEffectEnum::Boost))
        {
            this->SetChildRenderBack(effObj);
        }
        else
        {
            this->SetChildRenderFront(effObj);
        }
    }
}

void CasterObject::OnUpdate(const float& dt)
{
    if (m_State == CasterObjectState::Attack && m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1) - 2)
    {
        SetAnimationPlayTime(0.5f);
        if (m_atk_callback != nullptr)
        {
            m_atk_callback();
            m_atk_callback = nullptr;
        }
    }

    if (m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1) - 1)
    {
        if (m_State == CasterObjectState::Die)
        {
            this->SetIsAnimationLoop(false);
            return;
        }

        if (m_ChannelCounter > 0)
        {
            SetState(CasterObjectState::Cast);
        }
        else
        {
            SetState(m_NextState);
        }
    }


    if (m_FlashTimer > 0.0f)
    {
        m_FlashTimer -= dt;
        bool isRed = (int)(m_FlashTimer * 10) % 2 == 0;
        glm::vec4 red = { 0.6f,0.0f,0.0f,1.0f };
        glm::vec4 normal = { 1.0f,1.0f,1.0f,1.0f };
        this->color = isRed ? red : normal;

        if (m_FlashTimer <= 0.0f) { m_FlashTimer = false; this->color = originColor; }
    }
    else
    {
        m_FlashTimer = 0.0f;
        originColor = this->color;
    }
}

void CasterObject::SetCaster(CasterType type, Element::Type element)
{
    if (m_CasterType != type && type == CasterType::BigBoss)
    {
        this->scale = { 640.0f, 640.0f, 1.0f };
    }
    m_CasterType = type;

    if (element == Element::Corrupt)element = Element::Earth;
    m_CasterElement = element;

    if (m_CasterType != CasterType::BigBoss)
    {
        std::cout << "SET TEXUTER " << CasterSpritePath[(int)type][(int)m_CasterElement] << "\n";

        SetTexture(CasterSpritePath[(int)type][(int)m_CasterElement]);
    }
    else
    {
        SetTexture(CorruptSpritePath);
        SetSpriteByIndex(static_cast<int>(m_CasterElement),this->GetCurrentAnimationColumn());
    }
}
void CasterObject::SetCaster(CasterType type, Element::Type element, CasterPosition pos)
{
    SetCaster(type, element);

    int flip = pos == CasterPosition::CasterA ? 1 : -1;

    this->scale.x *= flip;

    float x = -CASTER_POSITION_X;
    float y = CASTER_POSITION_Y;

    if (m_CasterType == CasterType::BigBoss)
    {
        y = 0.0f;
    }

    this->position = { x * flip, y,0.0f };
}

void CasterObject::PlayChannelAnim(int ChannelCount)
{
    if (ChannelCount != 0)
    {
        m_ChannelCounter += ChannelCount;
        SetState(CasterObjectState::Cast);
    }
    else
    {
        SetState(CasterObjectState::Cast, CasterObjectState::Idle);
    }

}

void CasterObject::PlayAttackAnim(bool isChannelSpell,std::function<void()> callback)
{
    std::function<void()> atk_callback = [this,isChannelSpell, callback]()
    {
        if (isChannelSpell)
        {
            m_ChannelCounter--;
        }

        callback();
    };

    m_atk_callback = atk_callback;
    SetState(CasterObjectState::Attack, CasterObjectState::Idle);
}

void CasterObject::PlayDiedAnim()
{
    SetState(CasterObjectState::Die);
}

void CasterObject::PlayEffect(SpellEffectEnum effect)
{
    m_Effects[effect]->Play();
}

void CasterObject::StopEffect(SpellEffectEnum effect)
{
    m_Effects[effect]->Stop();
}


