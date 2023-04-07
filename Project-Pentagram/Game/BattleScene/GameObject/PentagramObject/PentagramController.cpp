#include "Engine/GameStateController.h"
#include "PentagramController.h"
#include "Game\BattleScene\BattleManager.h"
#include <math.h>

void CastSpell()
{
    auto bm = BattleManager::GetInstance();
    CastSpellDetail* spell = bm->Data.GetCurrentCaster()->CastSpell();
    bm->SwapCaster();
}

int& PentragramController::FieldData(PentagramField field)
{
    switch (field)
    {
    case PentagramField::Circle:
        return m_currentData.circle;
    case PentagramField::Complex:
        return m_currentData.complex;
    case PentagramField::Will:
        return m_currentData.will;
    case PentagramField::Effect:
        return m_currentData.effect;
    case PentagramField::Time:
        return m_currentData.time;
    }
}

PentragramController::PentragramController(IGameObjectManager* scene) :m_ObjectManager(scene)
{
    m_PentragramCircle = m_ObjectManager->CreateObject(new PentagramCircleUI(m_ObjectManager));
    m_PentragramFieldButtons = m_ObjectManager->CreateObject(new PentagramFieldButtonUI(m_ObjectManager));
    m_PentagramScrollButton = m_ObjectManager->CreateObject(new PentagramScrollButtonManagerUI(m_ObjectManager));

    m_PentragramFieldButtons->OnFieldButtonClicked.AddListener([this](PentagramField field) {this->SetPentagramField(field); });
    m_PentagramScrollButton->OnScrollButtonClicked.AddListener([this](int value) {this->SetPentagramValue(value); });

    OnPentagramValueChange.AddListener([this](PentagramEvent e)
        {
            m_LastestEvent = e;
    m_PentragramCircle->UpdateCircleUI(m_LastestEvent);
    m_PentagramScrollButton->SetScrollMode(m_LastestEvent);
        });

#pragma region OtherButton
    m_CastButton = m_ObjectManager->CreateObject(new ScrollButton("Cast"));
    m_CastButton->position = { -180.0f, -440.0f - PENTAGRAM_CIRCLE_OFFSET_Y, 0.0f };
    m_CastButton->onClick = [](Button* button)
    {
        AudioController::GetInstance()->PlaySFX("Audio/SFX/UI/Game/sfx_ui_game_invoke_button_press.wav", 1.0f);
        CastSpell();
    };

    m_PassButton = m_ObjectManager->CreateObject(new ScrollButton("Pass"));
    m_PassButton->position = { 180.0f, -440.0f - PENTAGRAM_CIRCLE_OFFSET_Y, 0.0f };
    m_PassButton->onClick = [](Button* button)
    {
        auto bm = BattleManager::GetInstance();
        bm->Data.GetCurrentCaster()->EndTurn(true);
        bm->SwapCaster();
    };

    m_PentragramCircle->SetChildRenderBack(m_CastButton);
    m_PentragramCircle->SetChildRenderBack(m_PassButton);
#pragma endregion

    m_SpellIcon = m_ObjectManager->CreateObject(new SpellIconUI("PentagramIcon"));
    m_PentragramCircle->SetChildRenderBack(m_SpellIcon);
    m_PentragramCircle->SetChildRenderFront(m_PentragramFieldButtons);

    m_PentragramCircle->SetPentagramUI(1, 1);
    m_SpellIcon->ToggleIsPentagramIcon(true);
}

void PentragramController::SetActive(const bool& active)
{
    m_PentragramCircle->SetActive(active);
    m_PentagramScrollButton->SetActive(active);

    m_CastButton->SetActive(active);
    m_PassButton->SetActive(active);

    m_SpellIcon->ToggleIsPentagramIcon(true);

    m_PentragramCircle->UpdateCircleUI(m_LastestEvent);
    m_PentagramScrollButton->SetScrollMode(m_LastestEvent);
}

void PentragramController::SetPentagramField(PentagramField selectedField)
{
    m_currentField = selectedField;
    OnPentagramValueChange.Invoke({ m_currentField,FieldData(m_currentField) });
}

void PentragramController::SetPentagramValue(int value)
{

    std::cout << "Value: " << value << "\n";

    if (m_currentField == PentagramField::Time)
    {
        value += m_currentData.time;
    }

    FieldData(m_currentField) = value < 1 ? 1 : value;

    OnPentagramValueChange.Invoke({ m_currentField,FieldData(m_currentField) });

    if (m_currentCaster == nullptr) return;

    OnPentagramDataChange.Invoke(m_currentData);
    if (m_currentCaster->GetCasterManager()->SetPentagramData(m_currentData))
    {
        m_currentData = m_currentCaster->GetCasterManager()->GetPentagramData();
        m_PentragramFieldButtons->SetFieldButtonRune(PentagramField::Time, 0);
    }

    m_SpellIcon->SetIcon(m_currentCaster->GetCasterManager()->GetSpellDetail(), false);

    m_currentCaster->GetCasterUI()->SetStat(m_currentCaster->GetCasterManager()->GetPreviewStat());

    BattleManager::GetInstance()->Data.Timeline.UI->UpdatePreviewIcon(m_currentCaster->GetCasterManager()->GetSpellDetail());

    m_PentragramFieldButtons->SetFieldButtonRune(m_currentField, m_currentCaster->GetCasterManager()->GetFieldCost(m_currentField));

    m_CastButton->SetActive(m_currentCaster->GetCasterManager()->CanCastSpell());
}

void PentragramController::SetPentagramOwner(CasterController* caster)
{
    m_currentCaster = caster;
    ResetPentagram();
}

void PentragramController::SetPentagramActive(MainObjectEnum obj, const bool& isActive)
{
    switch (obj) {
    case MainObjectEnum::Pentagram:
        this->SetActive(isActive);
        break;
    case MainObjectEnum::PentagramCircleUI:
        m_PentragramCircle->SetActive(isActive);
        if (isActive)
        {
            m_PentragramCircle->UpdateCircleUI(m_LastestEvent);
        }
        break;
    case MainObjectEnum::PentagramTimeB:
        m_PentragramFieldButtons->SetFieldButtonActive(PentagramField::Time, isActive);
        break;
    case MainObjectEnum::PentagramCircleB:
        m_PentragramFieldButtons->SetFieldButtonActive(PentagramField::Circle, isActive);
        break;
    case MainObjectEnum::PentagramComplexB:
        m_PentragramFieldButtons->SetFieldButtonActive(PentagramField::Complex, isActive);
        break;
    case MainObjectEnum::PentagramWillB:
        m_PentragramFieldButtons->SetFieldButtonActive(PentagramField::Will, isActive);
        break;
    case MainObjectEnum::PentagramEffectB:
        m_PentragramFieldButtons->SetFieldButtonActive(PentagramField::Effect, isActive);
        break;
    case MainObjectEnum::PentagramScroll:
        m_PentagramScrollButton->SetActive(isActive);
        if (isActive)
        {
            m_PentagramScrollButton->SetScrollMode(m_LastestEvent);
        }
        break;
    case MainObjectEnum::CastButton:
        m_CastButton->SetActive(isActive);
        break;
    case MainObjectEnum::PassButton:
        m_PassButton->SetActive(isActive);
        break;
    }
}

void PentragramController::ResetPentagram()
{
    m_currentData = { 1,1,1,1,0 };
    m_currentCaster->GetCasterManager()->SetPentagramData(m_currentData);
    m_currentData = m_currentCaster->GetCasterManager()->GetPentagramData();

    SetPentagramField(PentagramField::Time);

    m_SpellIcon->ToggleIsPentagramIcon(true);
    m_SpellIcon->SetIcon(m_currentCaster->GetCasterManager()->GetSpellDetail(), false);

    BattleManager::GetInstance()->Data.Timeline.UI->UpdatePreviewIcon(m_currentCaster->GetCasterManager()->GetSpellDetail());

    m_PentragramFieldButtons->ToggleButton(PentagramField::Time);
    m_PentragramFieldButtons->ResetFieldRune();

    m_PentragramCircle->SetPentagramUI(1, 1);

}
void PentragramController::ResetPentagramButtonField()
{
    SetPentagramField(m_currentField);
    m_PentragramFieldButtons->ToggleButton(m_currentField);

    m_PentragramCircle->SetPentagramUI(m_PentragramCircle->GetCircleValue(), m_PentragramCircle->GetComplexValue());
}

