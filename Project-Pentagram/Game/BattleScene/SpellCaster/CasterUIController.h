﻿#pragma once
#include "Game/GameData/CasterData/CasterStat.h"
#include "Game/GameData/CasterData/CasterPosition.h"
#include "Game/BattleScene/GameObject/CasterDetailUI.h"
#include "Game/BattleScene/GameObject/SpellDetailUI.h"
#include "Game/BattleScene/ManaRoulette/ManaRouletteUI.h"

class CasterUIController
{
private:
    CasterDetailUI* m_StatUI;
    SpellDetailUI* m_DetailBox;
    bool m_IsShowDetailBox;
    ManaRouletteUI* m_Roulette;
public:
    CasterUIController(CasterPosition position);

    void SetStat(CasterStat stat);
    void SetIsShowDetail(bool active);
    bool IsShowDetail() const;
    bool IsReadyToShowDetail() const;
    void SetDetail(CastSpellDetail* spell, bool isMainData = false, glm::vec3 IconPos = { 0,0,0 });
    void UpdateEffectBar(std::vector<EffectDetail_T> effects);

    void SetWheelValue(std::array<int, 6> numbers);
    void SetWheelActive(bool isActive);
    bool IsWheelActive() const;
    void SpinWheel(int n, std::function<void()> callback);
    void ResetWheel();

    void SetActive(bool isActive);

};