#pragma once
#include "jhAnimatedGameObject.h"


namespace jh
{
	struct SkillAnimationInfo
	{
		float Width;
		float Height;
		float Mag;
		jh::math::Vector2 Offset;
		UINT SpriteCount;
		float AnimationDuration;
		SkillAnimationInfo()
			: Width(0.0f)
			, Height(0.0f)
			, Mag(0.0f)
			, Offset(jh::math::Vector2::Zero)
			, SpriteCount(0)
			, AnimationDuration(0.0f)
		{
		}
	};

	class Animator;
	class PlayerScript;
	class PlayerSkillObject final : public AnimatedGameObject
	{
	public:
		PlayerSkillObject(const ePlayerSkillType eSkillType, PlayerScript* pPlayerScript, const std::wstring& textureKey, const std::wstring& materialKey, SkillAnimationInfo& animInfo);
		virtual ~PlayerSkillObject() = default;


	public:
		static const std::wstring ELECTRIC_BEAM_ANIM_KEY;

	private:
		Animator* setAnimator(const std::wstring& textureKey, SkillAnimationInfo& animInfo);
		void setRenderer(const std::wstring& materialKey);
		void setScript(PlayerScript* pPlayerScript, Animator* pAnimator);
		void setTransform(PlayerScript* pPlayerScript);
	private:
		ePlayerSkillType		meSkillType;
	};
}
