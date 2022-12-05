#include "Engine/GameStateController.h"
#include "PentagramController.h"
#include "Game\BattleScene\BattleManager.h"
#include <math.h>

void CastSpell()
{
    auto bm = BattleManager::GetInstance();
    auto spell = bm->Data.GetCurrentCaster()->CastSpell();

    bool doCompare = true;
    switch (spell->OriginalSpell->GetChannelEffectType())
    {
    case ChannelEffectEnum::None:
        doCompare = true;
        break;
    case ChannelEffectEnum::Wait:
        doCompare = false;
        break;
    case ChannelEffectEnum::Active:
        doCompare = true;
        break;
    }

    bm->Data.Timeline.AddSpellToTimeline(spell, true);
    bm->Data.GetCurrentCaster()->GetCasterObject()->PlayChannelAnim();
    bm->Data.GetCurrentCaster()->EndTurn();
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

    m_PentragramFieldButtons->OnFieldButtonClicked.AddListenner([this](PentagramField field) {this->SetPentagramField(field);});
    m_PentagramScrollButton->OnScrollButtonClicked.AddListenner([this](int value) {this->SetPentagramValue(value); });

    OnPentagramValueChange.AddListenner([this](PentagramEvent e)
        {
            m_PentragramCircle->UpdateCircleUI(e);
            m_PentagramScrollButton->SetScrollMode(e);
        });

#pragma region OtherButton
    m_CastButton = m_ObjectManager->CreateButton("Cast");
    m_CastButton->SetIsSlicing(true);
    m_CastButton->SetSlicingBorderSize(160.0f);
    m_CastButton->SetSlicingBorderMultiplier(0.25f);
    m_CastButton->SetSlicingType(SlicingType::REPEAT);
    m_CastButton->position = { -160.0f,-460.0f,0.0f };
    m_CastButton->scale = { 240.0f, 160.0f, 1.0f };
    m_CastButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_CastButton->onHover = [](Button* button) {  button->scale = { 260.0f, 160.0f, 1.0f }; };
    m_CastButton->unHover = [](Button* button) { button->scale = { 240.0f, 160.0f, 1.0f }; };
    m_CastButton->textObject.text = "Cast";
    m_CastButton->SetTexture("Sprites/UI/Game/ui_game_scroll.png");
    m_CastButton->SetIsSlicing(false);
    m_CastButton->onClick = [](Button* button)
    {
        CastSpell();
    };

    m_PassButton = m_ObjectManager->CreateButton("Pass");
    m_PassButton->SetIsSlicing(true);
    m_PassButton->SetSlicingBorderSize(160.0f);
    m_PassButton->SetSlicingBorderMultiplier(0.25f);
    m_PassButton->SetSlicingType(SlicingType::REPEAT);
    m_PassButton->position = { 160.0f,-460.0f,0.0f };
    m_PassButton->scale = { 240.0f, 160.0f, 1.0f };
    m_PassButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_PassButton->onHover = [](Button* button) {  button->scale = { 260.0f, 160.0f, 1.0f }; };
    m_PassButton->unHover = [](Button* button) { button->scale = { 240.0f, 160.0f, 1.0f }; };
    m_PassButton->textObject.text = "Pass";
    m_PassButton->SetTexture("Sprites/UI/Game/ui_game_scroll.png");
    m_PassButton->SetIsSlicing(false);
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
    m_SpellIcon->ToggleIconOverlay(false);
}

void PentragramController::SetActive(const bool& active)
{
    m_PentragramCircle->SetActive(active);
    m_PentragramFieldButtons->SetActive(active);
    m_PentagramScrollButton->SetActive(active);
    m_CastButton->SetActive(active);
    m_PassButton->SetActive(active);

    m_SpellIcon->ToggleIconOverlay(false);
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

    BattleManager::GetInstance()->Data.Timeline.UI->UpdatePreviewIcon(m_currentCaster->GetCasterManager()->GetSpellDetail());

    m_PentragramFieldButtons->SetFieldButtonRune(m_currentField, m_currentCaster->GetCasterManager()->GetFieldCost(m_currentField));

    m_CastButton->SetActive(m_currentCaster->GetCasterManager()->CanCastSpell());
}

void PentragramController::SetPentagramOwner(CasterController* caster)
{
    m_currentCaster = caster;
    ResetPentagram();
}

void PentragramController::ResetPentagram()
{
    m_currentData = { 1,1,1,1,0 };
    m_currentCaster->GetCasterManager()->SetPentagramData(m_currentData);
    m_currentData = m_currentCaster->GetCasterManager()->GetPentagramData();

    SetPentagramField(PentagramField::Time);

    m_SpellIcon->SetIcon(m_currentCaster->GetCasterManager()->GetSpellDetail(), false);

    BattleManager::GetInstance()->Data.Timeline.UI->UpdatePreviewIcon(m_currentCaster->GetCasterManager()->GetSpellDetail());

    m_PentragramFieldButtons->ResetFieldRune();

    m_SpellIcon->ToggleIconOverlay(false);
}

