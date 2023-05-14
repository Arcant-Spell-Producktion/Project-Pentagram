#include "Engine/GameStateController.h"
#include "PentagramController.h"
#include "Game\BattleScene\BattleManager.h"
#include <math.h>

void CastSpell()
{
    BattleManager& bm = BattleManager::GetInstance();
    CastSpellDetail* spell = bm.Data.GetCurrentCaster()->CastSpell();
    bm.SwapCaster();
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

void PentragramController::TogglePentagramField(PentagramField field, bool isActive)
{
    m_PentragramFieldButtons->SetFieldButtonActive(field, isActive);
    if (isActive)
    {
        SetPentagramField(field);
    }

}

PentragramController::PentragramController(IGameObjectManager* scene) :m_ObjectManager(scene)
{
    m_PentragramCircle = m_ObjectManager->CreateObject(new PentagramCircleUI(m_ObjectManager));
    m_PentragramFieldButtons = m_ObjectManager->CreateObject(new PentagramFieldButtonUI(m_ObjectManager));
    m_PentagramScrollButton = m_ObjectManager->CreateObject(new PentagramScrollButtonManagerUI(m_ObjectManager));
    m_PentagramSpellSelector = m_ObjectManager->CreateObject(new PentagramSpellSelector());

    m_PentragramFieldButtons->OnFieldButtonClicked.AddListener([this](PentagramField field) {this->SetPentagramField(field); });
    m_PentagramScrollButton->OnScrollButtonClicked.AddListener([this](int value) {this->SetPentagramValue(value); });

    m_PentagramSpellSelector->OnSpellClick.AddListener([this](PentagramData_T data) {this->SetPentagramData(data); });

    OnPentagramValueChange.AddListener([this](PentagramEvent e)
        {
            m_LastestEvent = e;
    m_PentragramCircle->UpdateCircleUI(m_LastestEvent);
    m_PentagramScrollButton->SetScrollMode(m_LastestEvent);
    m_PentagramSpellSelector->UpdateSpellIcons(m_LastestEvent);
    m_currentCaster->GetCasterUI()->SetStat(m_currentCaster->GetCasterManager()->GetPreviewStat());

        });

#pragma region OtherButton
    m_CastButton = m_ObjectManager->CreateObject(new ScrollButton("Cast"));
    m_CastButton->position = { -180.0f, -440.0f - PENTAGRAM_CIRCLE_OFFSET_Y, 0.0f };
    m_CastButton->onClick = [](Button* button)
    {
        AudioController::GetInstance().PlaySFX("Audio/SFX/UI/Game/sfx_ui_game_invoke_button_press.wav", 1.0f);
        CastSpell();
    };

    m_PassButton = m_ObjectManager->CreateObject(new ScrollButton("Pass"));
    m_PassButton->position = { 180.0f, -440.0f - PENTAGRAM_CIRCLE_OFFSET_Y, 0.0f };
    m_PassButton->onClick = [](Button* button)
    {
        BattleManager& bm = BattleManager::GetInstance();
        bm.Data.GetCurrentCaster()->EndTurn(true);
        bm.SwapCaster();
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

void PentragramController::SetPentagramData(PentagramData_T data)
{
    m_currentData = data;
    m_currentCaster->GetCasterManager()->SetPentagramData(m_currentData);
    m_currentData = m_currentCaster->GetCasterManager()->GetPentagramData();

    m_SpellIcon->ToggleIsPentagramIcon(true);
    m_SpellIcon->SetIcon(m_currentCaster->GetCasterManager()->GetSpellDetail(), false);
    BattleManager::GetInstance().Data.Timeline.UI->UpdatePreviewIcon(m_currentCaster->GetCasterManager()->GetSpellDetail());

    SetPentagramField(PentagramField::Time);

    m_PentragramFieldButtons->ToggleButton(PentagramField::Time);

    m_PentragramCircle->SetPentagramUI(m_currentData.circle, m_currentData.complex);

    m_PentragramFieldButtons->SetFieldButtonRune(PentagramField::Time, m_currentCaster->GetCasterManager()->GetFieldValue(PentagramField::Time));
    m_PentragramFieldButtons->SetFieldButtonRune(PentagramField::Circle, m_currentCaster->GetCasterManager()->GetFieldValue(PentagramField::Circle));
    m_PentragramFieldButtons->SetFieldButtonRune(PentagramField::Complex, m_currentCaster->GetCasterManager()->GetFieldValue(PentagramField::Complex));
    m_PentragramFieldButtons->SetFieldButtonRune(PentagramField::Will, m_currentCaster->GetCasterManager()->GetFieldValue(PentagramField::Will));
    m_PentragramFieldButtons->SetFieldButtonRune(PentagramField::Effect, m_currentCaster->GetCasterManager()->GetFieldValue(PentagramField::Effect));
}

void PentragramController::SetActive(const bool& active)
{
    m_PentragramCircle->SetActive(active);
    m_PentagramScrollButton->SetActive(active);
    m_PentagramSpellSelector->SetActive(active);

    m_CastButton->SetActive(active);
    m_PassButton->SetActive(active);

    if(active)
    {
        m_SpellIcon->ToggleIsPentagramIcon(true);
        m_PentragramCircle->UpdateCircleUI(m_LastestEvent);
        m_PentagramScrollButton->SetScrollMode(m_LastestEvent);
        m_PentagramSpellSelector->UpdateSpellIcons(m_LastestEvent);
    }

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

    BattleManager::GetInstance().Data.Timeline.UI->UpdatePreviewIcon(m_currentCaster->GetCasterManager()->GetSpellDetail());

    m_PentragramFieldButtons->SetFieldButtonRune(m_currentField, m_currentCaster->GetCasterManager()->GetFieldValue(m_currentField));

    m_CastButton->SetActive(m_currentCaster->GetCasterManager()->CanCastSpell());
}

void PentragramController::SetPentagramOwner(CasterController* caster)
{
    m_currentCaster = caster;
    Element::Type element = m_currentCaster->GetCasterManager()->Data().Element();
    m_PentragramFieldButtons->SetElement(element);
    m_PentagramSpellSelector->SetElement(element);
    m_PentragramCircle->SetElement(element);
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
        TogglePentagramField(PentagramField::Time, isActive);
        break;
    case MainObjectEnum::PentagramCircleB:
        TogglePentagramField(PentagramField::Circle, isActive);
        break;
    case MainObjectEnum::PentagramComplexB:
        TogglePentagramField(PentagramField::Complex, isActive);
        break;
    case MainObjectEnum::PentagramWillB:
        TogglePentagramField(PentagramField::Will, isActive);
        break;
    case MainObjectEnum::PentagramEffectB:
        TogglePentagramField(PentagramField::Effect, isActive);
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

    if (true)
    {
        
    }
}

void PentragramController::ResetPentagram()
{
    SetPentagramData({ 1,1,1,1,0 });
    m_PentragramFieldButtons->ResetFieldRune();
}
void PentragramController::ResetPentagramButtonField()
{
    SetPentagramField(m_currentField);
    m_PentragramFieldButtons->ToggleButton(m_currentField);

    m_PentragramCircle->SetPentagramUI(m_PentragramCircle->GetCircleValue(), m_PentragramCircle->GetComplexValue());
}

GameObject* PentragramController::GetPentagramObject(MainObjectEnum obj) const
{
    GameObject* objPtr = nullptr;

    switch (obj) {
    case MainObjectEnum::Pentagram:
        break;
    case MainObjectEnum::PentagramCircleUI:
            objPtr = m_PentragramCircle;
        break;
    case MainObjectEnum::PentagramTimeB:
        objPtr = m_PentragramFieldButtons->GetButtonByField(PentagramField::Time);
        break;
    case MainObjectEnum::PentagramCircleB:
        objPtr = m_PentragramFieldButtons->GetButtonByField(PentagramField::Circle);
        break;
    case MainObjectEnum::PentagramComplexB:
        objPtr = m_PentragramFieldButtons->GetButtonByField(PentagramField::Complex);
        break;
    case MainObjectEnum::PentagramWillB:
        objPtr = m_PentragramFieldButtons->GetButtonByField(PentagramField::Will);
        break;
    case MainObjectEnum::PentagramEffectB:
        objPtr = m_PentragramFieldButtons->GetButtonByField(PentagramField::Effect);
        break;
    case MainObjectEnum::PentagramScroll:
        objPtr = m_PentagramScrollButton;
        break;
    case MainObjectEnum::CastButton:
        objPtr = m_CastButton;
        break;
    case MainObjectEnum::PassButton:
        objPtr = m_PassButton;
        break;
    }

    return objPtr;
}

