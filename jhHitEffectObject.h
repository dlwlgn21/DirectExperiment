#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	class Texture;
	class MonsterScript;
	class HitEffectObject : public AnimatedGameObject
	{
	public:
		HitEffectObject();
		virtual ~HitEffectObject() = default;

		void SetScriptAndAnimKey(Script* pScript, const std::wstring& animKey);
		void SetEffectAnimation(Texture* pAtlas, const float width, const float height, const std::wstring& animKey, const UINT spriteCount, const float duration);

	protected:
		void setRenderer() override;
	};
}

