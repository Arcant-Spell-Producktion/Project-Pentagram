#include "BaseEffectObject.h"
#include "Engine/Audio/AudioController.h"

#include <string>

const std::string EffectTexturePath[] =
{
    "Sprites/StatusEffect/Mark.png",
    "Sprites/StatusEffect/Burn.png",
    "Sprites/StatusEffect/Overflow.png",
    "Sprites/StatusEffect/Freeze.png",
    "Sprites/StatusEffect/Fortify.png",
    "Sprites/StatusEffect/Petrify.png",
    "Sprites/StatusEffect/Boost.png",
};

BaseEffectObject::BaseEffectObject(SpellEffectEnum effect) :
    GameObject("EffectObject_" + SpellEffectType::GetString(effect)),
    m_Type(effect)
{
    this->SetTexture(EffectTexturePath[static_cast<int>(m_Type) - 1]);
    m_Row = GetTexture()->GetImageRow();

    this->scale = { 320.0f, 320.0f, 1.0f };

    //Set Effect Play Mode
    switch (m_Type) {
    case SpellEffectEnum::Mark:
        m_PlayMode = EffectObjectPlayMode::Freeze;
        break;
    case SpellEffectEnum::Burn:
        m_PlayMode = EffectObjectPlayMode::Once;
        break;
    case SpellEffectEnum::Overflow:
        m_PlayMode = EffectObjectPlayMode::Loop;
        break;
    case SpellEffectEnum::Freeze:
        m_PlayMode = EffectObjectPlayMode::Loop;
        break;
    case SpellEffectEnum::Fortify:
        m_PlayMode = EffectObjectPlayMode::Loop;
        this->scale = { 640.0f, 320.0f, 1.0f };
        break;
    case SpellEffectEnum::Petrify:
        m_PlayMode = EffectObjectPlayMode::Freeze;
        break;
    case SpellEffectEnum::Boost:
        m_PlayMode = EffectObjectPlayMode::Loop;
        break;
    }

    this->SetIsAnimationLoop(m_PlayMode != EffectObjectPlayMode::Freeze);
    this->SetIsAnimationObject(false);

    this->SetActive(false);
}

void BaseEffectObject::Play()
{
    isPlaying = true;

    this->SetActive(true);
    this->SetSpriteByIndex(0, 0);
    this->SetIsAnimationObject(isPlaying);

    switch (m_Type) 
    {
        case SpellEffectEnum::Mark:
            AudioController::GetInstance().PlaySFX("Audio/SFX/Gameplay/Effect/sfx_gameplay_effect_fire_1_mark.wav", 1.0f);
            break;
        case SpellEffectEnum::Burn:
            AudioController::GetInstance().PlaySFX("Audio/SFX/Gameplay/Effect/sfx_gameplay_effect_fire_2_burning.wav", 1.0f);
            break;
        case SpellEffectEnum::Overflow:
            AudioController::GetInstance().PlaySFX("Audio/SFX/Gameplay/Effect/sfx_gameplay_effect_water_2_overflow.wav", 1.0f);
            break;
        case SpellEffectEnum::Freeze:
            AudioController::GetInstance().PlaySFX("Audio/SFX/Gameplay/Effect/sfx_gameplay_effect_water_1_freeze.wav", 1.0f);
            break;
        case SpellEffectEnum::Fortify:
            AudioController::GetInstance().PlaySFX("Audio/SFX/Gameplay/Effect/sfx_gameplay_effect_earth_1_fortify.wav", 1.0f);
            break;
        case SpellEffectEnum::Petrify:
            AudioController::GetInstance().PlaySFX("Audio/SFX/Gameplay/Effect/sfx_gameplay_effect_earth_2_petrify.wav", 1.0f);
            break;
        case SpellEffectEnum::Boost:
            AudioController::GetInstance().PlaySFX("Audio/SFX/Gameplay/Effect/sfx_gameplay_effect_wind_1_Boost.wav", 1.0f);
            break;
    }

}

void BaseEffectObject::Stop()
{
    isPlaying = false;
}

void BaseEffectObject::OnUpdate(const float& dt)
{
    if (isPlaying)
    {
        if (m_PlayMode == EffectObjectPlayMode::Once)
        {
            if (m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1))
            {
                isPlaying = false;
                this->SetActive(false);
            }
        }
        else if (m_PlayMode == EffectObjectPlayMode::Freeze)
        {
            if (m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1))
            {
                this->SetIsAnimationObject(false);
            }
        }
        else if (m_PlayMode == EffectObjectPlayMode::Loop)
        {
            if (m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1) && m_CurrentAnimationRow == 1)
            {
                this->SetSpriteByIndex(1, 0, true);
            }
        }
    }
    else
    {
        if (IsActive())
        {
            if (m_PlayMode == EffectObjectPlayMode::Once)
            {
                if (m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1))
                {
                    isPlaying = false;
                    this->SetActive(false);
                }
            }
            else if (m_PlayMode == EffectObjectPlayMode::Freeze)
            {
                if (m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1))
                {
                    this->SetActive(false);
                }
            }
            else if (m_PlayMode == EffectObjectPlayMode::Loop)
            {
                if (m_CurrentAnimationColumn == GetAnimationColumn(m_CurrentAnimationRow - 1))
                {
                    if (GetCurrentAnimationRow() == 2)
                    {
                        this->SetSpriteByIndex(2, 0, true);
                    }
                    else
                    {
                        this->SetActive(false);
                    }
                }
            }
        }
    }
}

