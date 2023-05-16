#include "PentagramSpellSelector.h"
#include "Game/Spells/SpellDatabase.h"

PentagramSpellSelector::PentagramSpellSelector(): UIObject("PentagramSpellSelector")
{
    this->color.a = 0.0f;
    this->position = { 400.0f, 90.0f, 0.0f };
    for (int circle = 0; circle < 3; circle++)
    {
        for (int complex = 0; complex < 3; complex++)
        {
            ClickableSpellIconUI* icon =
                new ClickableSpellIconUI("SelectorSpellIcon_" + std::to_string(circle) + "_" + std::to_string(complex));

            icon->OnSpellClick.AddListener([this](int index) {ClickIcon(index); });

            Spell* spell =SpellDatabase::GetInstance().GetBookByElement(m_CurrentElement)->GetSpellByIndex(circle*3 + complex);

            CastSpellDetail* spellDetail = new CastSpellDetail(CasterPosition::CasterA, spell,1,1);

            icon->SetIcon(spellDetail,false);
            icon->SetOverlayToggle(false);

            m_SpellIcons[circle][complex] = icon;

            this->SetChildRenderFront(icon);

            //display icon in grid pattern and (circle = 1, complex = 1) is center
            float distant = 100.0f;
            icon->position = glm::vec3((complex - 1) * distant, (circle - 1) * -distant, 0.0f);

        }
    }

    m_SpellDetailUI = new SpellDetailUI({ 0.0f, 0.0f, 0.0f }, { 560.0f, 210.0f, 1.0f }, 28.0f);
    m_SpellDetailUI->SetActive(false);
    this->SetChildRenderFront(m_SpellDetailUI);

    m_ParticleSystem = new ParticleSystem("SelectedSpellParticle");
    m_ParticleSystem->SetTexture("Sprites/Particle/particle.png");
    m_ParticleSystem->SetSpriteByIndex(4, 0);

    ParticleProperty particleProp;

    particleProp.colorBegin = { 1.0f, 1.0f, 1.0f, 1.0f };
    particleProp.colorEnd = { 1.0f, 1.0f, 1.0f, 0.6f };
    particleProp.sizeBegin = 40.0f;
    particleProp.sizeEnd = 10.0f;
    particleProp.rotationVariation = 360.0f;
    particleProp.velocity = { 0.0f, 0.0f };
    particleProp.velocityVariation = { 50.0f, 50.0f };
    particleProp.lifeTime = 1.0f;

    m_ParticleSystem->baseParticle = particleProp;
    m_ParticleSystem->SetSpawnTime(0.01f);
    m_ParticleSystem->Emit(particleProp);

    this->SetChildRenderBack(m_ParticleSystem);
    m_ParticleSystem->position = m_SpellIcons[0][0]->position;
}

void PentagramSpellSelector::SetElement(Element::Type element)
{
    m_CurrentElement = element;
    Reset();
}

void PentagramSpellSelector::UpdateSpellIcons(PentagramEvent e)
{
    this->SetActive(e.Field == PentagramField::Circle || e.Field == PentagramField::Complex);

    switch (e.Field) {
    case PentagramField::Circle:
        m_IsHighlightColumn = true;
        m_Circle = e.Value;
        break;

    case PentagramField::Complex:
        m_IsHighlightColumn = false;
        m_Complex = e.Value;
        break;

    case PentagramField::Will:
        m_Will = e.Value;
        break;

    case PentagramField::Effect: 
        m_Effect = e.Value;
        break;

    default:break;
    }
    UpdateIconDetail();
}

void PentagramSpellSelector::Reset()
{
    m_Circle = 1;
    m_Complex = 1;
    m_Will = 1;
    m_Effect = 1;
    UpdateIconDetail();
}

void PentagramSpellSelector::UpdateIconDetail()
{
    ClickableSpellIconUI* icon = nullptr;
    for (int circle = 0; circle < 3; circle++)
    {
        for (int complex = 0; complex < 3; complex++)
        {
            icon = m_SpellIcons[circle][complex];

            Spell* spell = SpellDatabase::GetInstance().GetBookByElement(m_CurrentElement)->GetSpellByIndex(circle * 3 + complex);

            CastSpellDetail* spellDetail = icon->SpellDetail->SetSpell(spell);

            spellDetail->SelectedWill = m_Will;
            spellDetail->SelectedEffect = m_Effect;

            icon->SetIcon(spellDetail, false);
            icon->SetOverlayToggle(false);

            if(!m_IsHighlightColumn)
            {
                m_SpellIcons[circle][complex]->SetDarken(m_Circle - 1 != circle);
            }
            else
            {
               m_SpellIcons[circle][complex]->SetDarken(m_Complex - 1 != complex);

            }

        }
    }

    m_ParticleSystem->position = m_SpellIcons[m_Circle - 1][m_Complex - 1]->position;

    CastSpellDetail* spellDetail = m_SpellIcons[m_Circle - 1][m_Complex - 1]->SpellDetail;
    m_SpellDetailUI->SetDetail(spellDetail, false, spellDetail->isHidden);
}

void PentagramSpellSelector::ClickIcon(int index)
{
    m_Circle = (index / 3) + 1;
    m_Complex = (index % 3) + 1;
    OnSpellClick.Invoke({ m_Circle,m_Complex,m_Will,m_Effect,0 });
}

void PentagramSpellSelector::OnUpdate(const float& dt)
{
    UIObject::OnUpdate(dt);

    SpellIconUI* hoverIcon = nullptr;

    float x = 325.0f;
    float y = 0.0f;
    for (int circle = 0; circle < 3; circle++)
    {
        for (int complex = 0; complex < 3; complex++)
        {

            if (m_SpellIcons[circle][complex]->IsBeingHover())
            {
                hoverIcon = m_SpellIcons[circle][complex];

                CastSpellDetail* spellDetail = hoverIcon->SpellDetail;

                m_SpellDetailUI->SetDetail(spellDetail, false, spellDetail->isHidden);
                m_SpellDetailUI->SetCasterPosition(spellDetail->SpellOwner);
                m_SpellDetailUI->SetActive(true);

                if (complex < 2)
                {
                    m_SpellDetailUI->position = hoverIcon->position + glm::vec3(x, y, 0.0f);
                }
                else
                {
                    m_SpellDetailUI->position = hoverIcon->position + glm::vec3(-x, y, 0.0f);
                }
                break;
            }
        }
    }

    if (hoverIcon == nullptr)
    {
        m_SpellDetailUI->SetActive(false);
    }
}