#include "BaseSpellObject.h"

void BaseSpellObject::Next()
{
    std::cout << "\tSpell::Next\n";
    m_TotalTime = 0.0f;
    if (m_SpellUpdateQueue.size() == 0) { m_SpellState = SpellObjectState::Done; return; }
    m_CurrentUpdateFunc = m_SpellUpdateQueue.front();
    m_SpellUpdateQueue.pop();
}

void BaseSpellObject::OnUpdate(const float& dt)
{
    std::cout << "Spell State: " << (int)m_SpellState << " , " << m_SpellUpdateQueue.size() << "\n";
    std::cout << "Spell :: Check Init or Done\n";
    if (m_SpellState == SpellObjectState::Init || m_SpellState == SpellObjectState::Done) return;
    if (m_CurrentUpdateFunc == nullptr) Next();
    m_TotalTime += dt;
    m_CurrentUpdateFunc(dt);
}

void BaseSpellObject::QueueUpdateFunction(SpellUpdateFunc func)
{
    std::cout << "Spell:: Add Update \n";

    m_SpellUpdateQueue.push(func);
}

void BaseSpellObject::Initialize()
{
    m_SpellState = SpellObjectState::Ready;
}

BaseSpellObject::BaseSpellObject(CasterPosition target, std::string spellName, std::string spellTexturePath) :GameObject(spellName)
{
    std::cout << "Spell State: " << (int)m_SpellState << " , " << m_SpellUpdateQueue.size() << "\n";

    m_SpellState = SpellObjectState::Init;

    if (target == CasterPosition::CasterB) m_SpellTarget = -1;
    this->scale.x = m_SpellTarget;

    this->SetTexture(spellTexturePath);
};