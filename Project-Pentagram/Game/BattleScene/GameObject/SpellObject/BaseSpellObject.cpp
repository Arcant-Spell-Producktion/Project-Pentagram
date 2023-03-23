#include "BaseSpellObject.h"

void BaseSpellObject::Next()
{
    m_TotalTime = 0.0f;
    if (m_SpellUpdateQueue.size() == 0) { m_SpellState = SpellObjectState::Done; return; }
    m_CurrentUpdateFunc = m_SpellUpdateQueue.front();
    m_SpellUpdateQueue.pop();
}

void BaseSpellObject::OnUpdate(const float& dt)
{
    if (m_SpellState == SpellObjectState::Init || m_SpellState == SpellObjectState::Done) return;
    if (m_CurrentUpdateFunc == nullptr) Next();
    
    m_TotalTime += dt;
    m_CurrentUpdateFunc(dt);

}

void BaseSpellObject::QueueUpdateFunction(SpellUpdateFunc func)
{
    m_SpellUpdateQueue.push(func);
}

void BaseSpellObject::Initialize()
{
    m_SpellState = SpellObjectState::Ready;
}

BaseSpellObject::BaseSpellObject(CasterPosition target, std::string spellName, std::string spellTexturePath) :GameObject(spellName)
{
    this->SetActive(false);

    m_SpellState = SpellObjectState::Init;

    if (target == CasterPosition::CasterA) m_SpellTarget = 1;
    else if (target == CasterPosition::CasterB) m_SpellTarget = -1;

    m_TexturePath = spellTexturePath;
    this->SetTexture(spellTexturePath);

    Trigger = false;

    QueueUpdateFunction([this](float dt) {});
        
}

void BaseSpellObject::Activate()
{
    if (m_SpellState >= SpellObjectState::Activate) { return; }

    while (m_SpellState < SpellObjectState::Ready) { std::cout << "NOT READY"; continue; }
    m_TotalTime = 0.0f;
    m_SpellState = SpellObjectState::Activate;
    this->SetActive(true);
    Next();
}
