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
    case ChannelEffectType::None:
        doCompare = true;
        break;
    case ChannelEffectType::Wait:
        doCompare = false;
        break;
    case ChannelEffectType::Active:
        doCompare = true;
        break;
    }

    bm->GetData()->Timeline.AddSpellToTimeline(spell,true);
    bm->GetData()->GetCurrentCaster()->EndTurn();
    bm->SwapCaster();
}

PentragramController::PentragramController(BattleScene* scene) :m_Scene(scene),GameObject("PentagramController")
{

    for (size_t i = 0; i < 5; i++)
    {
        float theta = 2.0f * 3.142526f * (i / 5.0f);
        
        float radius = 200.0f;
        float x_offset = 0.0f;
        float y_offset = 80.0f;
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
        
        button->position = { radius * sinf(theta) + x_offset,radius * cosf(theta)+y_offset ,0.0f };
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
        button->position = {-420.0f + ( i * 120.0f),-250.0f,0.0f};
        button->scale = { 80.0f, 80.0f, 1.0f };
        button->color = { 1.0f, 1.0f, 1.0f, 1.0f };
        button->textObject.text = std::to_string(i);
        button->textObject.textAlignment = TextAlignment::MID;
        button->textObject.position = { 0.0f, 0.0f, 0.0f };
        button->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
        button->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
        button->SetTexture(ButtonTexturePath);

        button->onClick = [this,i](Button* button) {SetPentagramValue(i); };

        m_IntButtons.push_back(button);
    }

    for (size_t i = 0; i < 2; i++)
    {
        Button* button = m_Scene->CreateButton("Arrow_" + std::to_string(i));
        button->position = { -80.0f + (i * 160.0f),-250.0f,0.0f };
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
    m_InvokeButton->position = { -120.0f,-360.0f,0.0f };
    m_InvokeButton->scale = { 160.0f, 80.0f, 1.0f };
    m_InvokeButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_InvokeButton->textObject.textAlignment = TextAlignment::MID;
    m_InvokeButton->textObject.position = { 0.0f, 0.0f, 0.0f };
    m_InvokeButton->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_InvokeButton->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
    m_InvokeButton->textObject.text = "Invoke";
    m_InvokeButton->SetTexture(ButtonTexturePath);
    m_InvokeButton->onClick = [](Button* button)
    {
        InvokeSpell();
    };

    m_PassButton = m_Scene->CreateButton("Pass");
    m_PassButton->position = { 120.0f,-360.0f,0.0f };
    m_PassButton->scale = { 160.0f, 80.0f, 1.0f };
    m_PassButton->color = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_PassButton->textObject.textAlignment = TextAlignment::MID;
    m_PassButton->textObject.position = { 0.0f, 0.0f, 0.0f };
    m_PassButton->textObject.color = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_PassButton->onHover = [](Button* button) { button->hoverColor = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f); };
    m_PassButton->textObject.text = "Pass";
    m_PassButton->SetTexture(ButtonTexturePath);
    m_PassButton->onClick = [](Button* button)
    {
        auto bm = BattleManager::GetInstance();
        bm->GetData()->GetCurrentCaster()->EndTurn(true);
        bm->SwapCaster();
    };

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
            m_IntButtons[i]->position = { -250.0f + ((i+1) * 120.0f),-250.0f,0.0f };
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(false);
        }
        break;
    case PentagramField::Will:
    case PentagramField::Effect:
        for (size_t i = 0; i < 6; i++)
        {
            m_IntButtons[i]->SetActive(true);
            m_IntButtons[i]->position = { -420.0f + ((i + 1) * 120.0f),-250.0f,0.0f };
        }
        for (size_t i = 0; i < 2; i++)
        {
            m_ArrowButtons[i]->SetActive(false);
        }
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
        break;
    }
}

void PentragramController::SetPentagramValue(int value)
{
    std::cout << "Value: " << value << "\n";
    switch (m_currentField)
    {
    case PentagramField::Circle:
        m_currentData.circle = value;
        break;
    case PentagramField::Complex:
        m_currentData.complex = value;
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

    auto caster = BattleManager::GetInstance()->GetData()->GetCurrentCaster()->GetSpellCaster();
    caster->SetPentagramData(m_currentData);

    if (m_currentField == PentagramField::Circle || m_currentField == PentagramField::Complex)
    {
        m_currentData.time = caster->GetSpellDetail()->OriginalSpell->GetCastTime();
        caster->SetPentagramData(m_currentData);
    }

    BattleManager::GetInstance()->GetData()->GetCurrentCaster()->GetCasterUI()->SetManaText((caster->GetMana() - caster->GetSpellCost()), caster->GetCasterData()->GetMana());
}