#include "Engine/GameStateController.h"
#include "PentagramController.h"
#include <Game/BattleScene/BattleManager.h>
#include <math.h>

const std::string ButtonTexturePath = "Sprites/Button_Test.png";

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

PentragramController::PentragramController() :m_ObjectManager(GameStateController::GetInstance()->currentScene), UIObject("PentagramController")
{
    this->color.a = 0.0f;

    float x_offset = 0.0f;
    float y_offset = 0.0f;

    m_Scroll_1 = m_ObjectManager->CreateUIObject("Scroll_1");
    m_Scroll_1->SetIsSlicing(true);
    m_Scroll_1->SetTexture("Sprites/UI/Game/ui_game_scroll.png");
    m_Scroll_1->SetSlicingBorderSize(200.0f);
    m_Scroll_1->SetSlicingBorderMultiplier(0.25f);
    m_Scroll_1->SetSlicingType(SlicingType::REPEAT);
    m_Scroll_1->position = { 0.0f,-300.0f,0.0f };
    m_Scroll_1->scale = { 800.0f, 160.0f,0.0f };
    this->SetChildRenderBack(m_Scroll_1);


    for (size_t i = 0; i < 4; i++)
    {
        float radius = 460.0f;

        UIObject* circle = m_ObjectManager->CreateUIObject("Circle_" + std::to_string(i));

        circle->SetIsAnimationObject(false);
        circle->position = { x_offset,y_offset,0.0f };
        circle->scale = { radius,radius,1.0f };
        circle->SetSpriteByIndex(i, 0);
        circle->SetTexture("Sprites/UI/Game/ui_game_pentagram.png");
        circle->SetActive(!(i > 1));
        if (i > 0)
        {
            circle->color.a = 0.8f;
        }

        m_PentragramObj.push_back(circle);
        this->SetChildRenderBack(circle);
    }

    for (size_t i = 0; i < 5; i++)
    {
        float theta = 2.0f * 3.142526f * (i / 5.0f);
        float radius = 200.0f;

        PentagramField field_value;

        switch (i)
        {
        case 0:
            field_value = PentagramField::Time;
            break;
        case 1:
            field_value = PentagramField::Complex;
            break;
        case 2:
            field_value = PentagramField::Effect;
            break;
        case 3:
            field_value = PentagramField::Will;
            break;
        case 4:
            field_value = PentagramField::Circle;
            break;
        }

        PentagramFieldButton* button = m_ObjectManager->CreateObject(new PentagramFieldButton(field_value,Element::Fire));

        button->onClick = [this, field_value](Button* button) { SetPentagramField(field_value); };

        button->position = { radius * sinf(theta) + x_offset,radius * cosf(theta) + y_offset ,0.0f };
        

        m_PentragramButtons.push_back(button);
        this->SetChildRenderBack(button);

    }

    for (size_t i = 1; i <= 6; i++)
    {
        Button* button = m_ObjectManager->CreateButton("Num_" + std::to_string(i));
        button->position = { -420.0f + (i * 120.0f),-300.0f,0.0f };
        button->scale = { 80.0f, 80.0f, 1.0f };
        button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button->SetIsSlicing(false);
        button->textObject.text = std::to_string(i);
        button->textObject.textAlignment = TextAlignment::MID;
        button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
        button->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
        button->SetTexture(ButtonTexturePath);

        button->onClick = [this, i](Button* button) {SetPentagramValue(i); };

        m_IntButtons.push_back(button);
        this->SetChildRenderBack(button);
    }

    for (size_t i = 0; i < 2; i++)
    {
        Button* button = m_ObjectManager->CreateButton("Arrow_" + std::to_string(i));
        button->position = { -80.0f + (i * 160.0f),-300.0f,0.0f };
        button->scale = { 120.0f, 80.0f, 1.0f };
        button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button->textObject.textAlignment = TextAlignment::MID;
        button->textObject.position = { 0.0f, 0.0f, 0.0f };
        button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
        button->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
        button->SetTexture(ButtonTexturePath);
        button->SetIsSlicing(false);

        if (i == 1)
        {
            button->textObject.text = "-->";
            button->onClick = [this, i](Button* button) {SetPentagramValue(1); };
        }
        else
        {
            button->textObject.text = "<--";
            button->onClick = [this, i](Button* button) {SetPentagramValue(-1); };
        }

        button->SetActive(false);

        m_ArrowButtons.push_back(button);
        this->SetChildRenderBack(button);
    }

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

    this->SetChildRenderBack(m_CastButton);
    this->SetChildRenderBack(m_PassButton);

    m_SpellIcon = m_ObjectManager->CreateObject(new SpellIconUI("PentagramIcon"));
    this->SetChildRenderBack(m_SpellIcon);

}

void PentragramController::SetActive(const bool& active)
{
    GameObject::SetActive(active);
    if (active)
    {
        auto field = m_currentField;

        PentragramController::SetPentagramField(PentagramField::Circle);
        PentragramController::SetPentagramValue(m_currentData.circle);

        PentragramController::SetPentagramField(PentagramField::Complex);
        PentragramController::SetPentagramValue(m_currentData.complex);

        PentragramController::SetPentagramField(PentagramField::Will);
        PentragramController::SetPentagramValue(m_currentData.will);

        PentragramController::SetPentagramField(PentagramField::Effect);
        PentragramController::SetPentagramValue(m_currentData.effect);

        PentragramController::SetPentagramField(field);
    }
}

int expand = 1;
void PentragramController::OnUpdate(const float& dt)
{
    float speed = 10.0f;
    float scale = m_PentragramObj[1]->scale.x + dt * 20.0f * expand;
    if (scale < 450.0f || scale > 480.0f)
    {
        expand *= -1;
    }

    for (size_t i = 1; i < 4; i++)
    {
        int direction = i % 2 == 0 ? 1 : -1;
        m_PentragramObj[i]->rotation += (dt * speed * i * direction);

        
        m_PentragramObj[i]->scale = { scale,scale,1.0f };
    }
}

void PentragramController::SetPentagramField(PentagramField selectedField)
{
    m_currentField = selectedField;
    std::cout << "Field: " << (int)selectedField << "\n";
    switch (m_currentField)
    {
    case PentagramField::Circle:
    case PentagramField::Complex:
        for (size_t i = 0; i < 6; i++)
        {
            if (i > 2)
            {
                m_IntButtons[i]->SetActive(false);
                continue;
            }
            m_IntButtons[i]->SetActive(true);
            m_IntButtons[i]->position.x = -240.0f + ((i + 1) * 120.0f);
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(false);
        }
        m_Scroll_1->scale = { 420.0f, 160.0f,0.0f };
        break;
    case PentagramField::Will:
    case PentagramField::Effect:
        for (size_t i = 0; i < 6; i++)
        {
            m_IntButtons[i]->SetActive(true);
            m_IntButtons[i]->position.x = -420.0f + ((i + 1) * 120.0f);
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(false);
        }
        m_Scroll_1->scale = { 800.0f, 160.0f,0.0f };
        break;
    case PentagramField::Time:
        for (size_t i = 0; i < 6; i++)
        {
            m_IntButtons[i]->SetActive(false);
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(true);
        }
        m_Scroll_1->scale = { 400.0f, 160.0f,0.0f };
        break;
    }

    for (auto penButton : m_PentragramButtons)
    {
        penButton->SetToggle(penButton->GetButtonField() == selectedField);
    }

}

void PentragramController::SetPentagramValue(int value)
{

    auto battleManager = BattleManager::GetInstance();
    auto currentCaster = battleManager->Data.GetCurrentCaster();
    auto spellCaster = currentCaster->GetCasterManager();

    std::cout << "Value: " << value << "\n";
    switch (m_currentField)
    {
    case PentagramField::Circle:
        m_currentData.circle = value;
        for (size_t i = 0; i < 4; i++)
        {
            if (i == 0)
            {
                m_PentragramObj[i]->SetSpriteByIndex(i, value - 1);
            }
            m_PentragramObj[i]->SetActive(i <= value);
        }
        break;
    case PentagramField::Complex:
        m_currentData.complex = value;
        for (size_t i = 1; i < 4; i++)
        {
            m_PentragramObj[i]->SetSpriteByIndex(i, value - 1);
        }
        break;
    case PentagramField::Will:
        m_currentData.will = value;
        break;
    case PentagramField::Effect:
        m_currentData.effect = value;
        break;
    case PentagramField::Time:
        m_currentData.time += value;
        m_currentData.time = m_currentData.time < 1 ? 1 : m_currentData.time;
        break;
    }

    spellCaster->SetPentagramData(m_currentData);

    if (m_currentField == PentagramField::Circle || m_currentField == PentagramField::Complex)
    {
        m_currentData.time = spellCaster->GetSpellDetail()->OriginalSpell->GetCastTime();
        spellCaster->SetPentagramData(m_currentData);
    }

    m_SpellIcon->SetIcon(spellCaster->GetSpellDetail());
    //currentCaster->GetCasterUI()->SetManaText((spellCaster->GetMana() - spellCaster->GetSpellCost()), spellCaster->GetCasterData()->GetMana());

    battleManager->Data.Timeline.UI->UpdatePreviewIcon(spellCaster->GetSpellDetail()->SelectedTime, spellCaster->GetSpellDetail());

    for (auto penButton : m_PentragramButtons)
    {
        if (penButton->GetButtonField() == m_currentField)
        {
            penButton->SetRuneActive(m_currentField == PentagramField::Time ? spellCaster->GetTimeCost() : value);
        }
    }
}

PentagramData_T PentragramController::ResetPentagram()
{
    SetPentagramField(PentagramField::Circle);
    SetPentagramValue(1);
    SetPentagramField(PentagramField::Complex);
    SetPentagramValue(1);
    SetPentagramField(PentagramField::Will);
    SetPentagramValue(1);
    SetPentagramField(PentagramField::Effect);
    SetPentagramValue(1);

    for (auto penButton : m_PentragramButtons)
    {
        penButton->SetRuneActive(penButton->GetButtonField() == PentagramField::Time ? 0 : 1);
    }

    return m_currentData;
}
