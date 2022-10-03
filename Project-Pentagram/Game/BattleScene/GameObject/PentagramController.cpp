#include "PentagramController.h"
#include <Game/BattleScene/BattleManager.h>
#include <math.h>

const std::string ButtonTexturePath = "Sprites/Button_Test.png";

void InvokeSpell()
{
    auto bm = BattleManager::GetInstance();
    auto spell = bm->GetData()->GetCurrentCaster()->CastSpell();

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

    bm->GetData()->Timeline.AddSpellToTimeline(spell, true);
    bm->GetData()->GetCurrentCaster()->EndTurn();
    bm->SwapCaster();
}

PentragramController::PentragramController() :m_Scene(GameStateController::GetInstance()->currentScene), GameObject("PentagramController")
{
    this->color.a = 0.0f;

    float x_offset = 0.0f;
    float y_offset = 0.0f;

    m_Scroll_1 = m_Scene->CreateUIObject("Scroll_1");
    m_Scroll_1->SetIsSlicing(true);
    m_Scroll_1->SetTexture("Sprites/UI/Game/ui_game_scroll.png");
    m_Scroll_1->SetSlicingBorderSize(160.0f);
    m_Scroll_1->position = { 0.0f,-300.0f,0.0f };
    m_Scroll_1->scale = { 800.0f, 160.0f,0.0f };

    for (size_t i = 0; i < 4; i++)
    {
        float radius = 460.0f;

        GameObject* circle = m_Scene->CreateGameObject("Circle_" + std::to_string(i), 4, { 3,3,3,3 });

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
    }

    for (size_t i = 0; i < 5; i++)
    {
        float theta = 2.0f * 3.142526f * (i / 5.0f);
        float radius = 200.0f;
        float _scale = 0.0f;

        std::string name;
        PentagramField field_value;

        switch (i)
        {
        case 0:
            name = "Will";
            field_value = PentagramField::Will;
            _scale = 120.0f;
            break;
        case 1:
            name = "Complex";
            field_value = PentagramField::Complex;
            _scale = 220.0f;
            break;
        case 2:
            name = "Effect";
            field_value = PentagramField::Effect;
            _scale = 180.0f;
            break;
        case 3:
            name = "Time";
            field_value = PentagramField::Time;
            _scale = 160.0f;
            break;
        case 4:
            name = "Circle";
            field_value = PentagramField::Circle;
            _scale = 180.0f;
            break;
        }

        Button* button = m_Scene->CreateButton("Field_" + std::to_string(i));

        button->textObject.text = name;

        button->onClick = [this, field_value](Button* button) {SetPentagramField(field_value); };

        button->position = { radius * sinf(theta) + x_offset,radius * cosf(theta) + y_offset ,0.0f };
        button->scale = { _scale, 80.0f, 1.0f };
        button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button->textObject.textAlignment = TextAlignment::MID;
        button->textObject.position = { 0.0f, 0.0f, 0.0f };
        button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
        button->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
        button->SetTexture(ButtonTexturePath);


        m_PentragramButtons.push_back(button);

    }

    for (size_t i = 1; i <= 6; i++)
    {
        Button* button = m_Scene->CreateButton("Num_" + std::to_string(i));
        button->position = { -420.0f + (i * 120.0f),-300.0f,0.0f };
        button->scale = { 80.0f, 80.0f, 1.0f };
        button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button->textObject.text = std::to_string(i);
        button->textObject.textAlignment = TextAlignment::MID;
        button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
        button->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
        button->SetTexture(ButtonTexturePath);

        button->onClick = [this, i](Button* button) {SetPentagramValue(i); };

        m_IntButtons.push_back(button);
    }

    for (size_t i = 0; i < 2; i++)
    {
        Button* button = m_Scene->CreateButton("Arrow_" + std::to_string(i));
        button->position = { -80.0f + (i * 160.0f),-300.0f,0.0f };
        button->scale = { 120.0f, 80.0f, 1.0f };
        button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button->textObject.textAlignment = TextAlignment::MID;
        button->textObject.position = { 0.0f, 0.0f, 0.0f };
        button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
        button->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
        button->SetTexture(ButtonTexturePath);

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
    }

    m_InvokeButton = m_Scene->CreateButton("Invoke");
    m_InvokeButton->SetIsSlicing(true);
    m_InvokeButton->SetSlicingBorderSize(160.0f);
    m_InvokeButton->position = { -160.0f,-460.0f,0.0f };
    m_InvokeButton->scale = { 240.0f, 160.0f, 1.0f };
    m_InvokeButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_InvokeButton->onHover = [](Button* button) {  button->scale = { 260.0f, 160.0f, 1.0f }; };
    m_InvokeButton->unHover = [](Button* button) { button->scale = { 240.0f, 160.0f, 1.0f }; };
    m_InvokeButton->textObject.text = "Invoke";
    m_InvokeButton->SetTexture("Sprites/UI/Game/ui_game_scroll.png");
    m_InvokeButton->onClick = [](Button* button)
    {
        InvokeSpell();
    };

    m_PassButton = m_Scene->CreateButton("Pass");
    m_PassButton->SetIsSlicing(true);
    m_PassButton->SetSlicingBorderSize(160.0f);
    m_PassButton->position = { 160.0f,-460.0f,0.0f };
    m_PassButton->scale = { 240.0f, 160.0f, 1.0f };
    m_PassButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_PassButton->onHover = [](Button* button) {  button->scale = { 260.0f, 160.0f, 1.0f }; };
    m_PassButton->unHover = [](Button* button) { button->scale = { 240.0f, 160.0f, 1.0f }; };
    m_PassButton->textObject.text = "Pass";
    m_PassButton->SetTexture("Sprites/UI/Game/ui_game_scroll.png");
    m_PassButton->onClick = [](Button* button)
    {
        auto bm = BattleManager::GetInstance();
        bm->GetData()->GetCurrentCaster()->EndTurn(true);
        bm->SwapCaster();
    };

    m_SpellIcon = new SpellIconUI("PentagramIcon");
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
}

void PentragramController::SetPentagramValue(int value)
{

    auto battleManager = BattleManager::GetInstance();
    auto currentCaster = battleManager->GetData()->GetCurrentCaster();
    auto spellCaster = currentCaster->GetSpellManager();

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
        m_SpellIcon->SetIcon(spellCaster->GetCasterData()->GetElement(), (m_currentData.circle - 1) * 3 + m_currentData.complex - 1);
    }

    currentCaster->GetCasterUI()->SetManaText((spellCaster->GetMana() - spellCaster->GetSpellCost()), spellCaster->GetCasterData()->GetMana());
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

    return m_currentData;
}
