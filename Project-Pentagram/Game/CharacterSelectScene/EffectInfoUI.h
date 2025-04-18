#pragma once
#include "Engine/UIObject.h"
#include "Engine/Renderer/TextObject.h"

#include "Utilities/Color.h"

class EffectInfoUI : public UIObject
{
	private:
		UIObject* m_EffectIcon;
		TextObject* m_EffectInfo;
	public:
		EffectInfoUI();

		void SetFitWithBorder(const glm::vec3 borderScale);
		void SetEffectIconTexture(const std::string& filePath);
		void SetEffectIconIndex(const glm::ivec2& index);
		void SetEffectInfo(const std::string& info);

		TextObject* GetEffectInfoText() const;
};
