#pragma once
#include "jhEngine.h"

namespace jh
{
	struct SkillAnimationInfo;
	class PlayerSkillObject;
	class PlayerScript;
	class PlayerSkillManager final
	{
	public:
		static PlayerSkillManager& GetInstance()
		{
			static PlayerSkillManager instance;
			return instance;
		}

		PlayerSkillManager(const PlayerSkillManager& other) = delete;
		PlayerSkillManager& operator=(const PlayerSkillManager& other) = delete;

		void Update();
		void SetPlayerScript(PlayerScript* pPlayerScript) { assert(pPlayerScript != nullptr); mpPlayerScript = pPlayerScript; }

		PlayerSkillObject* MakePlayerSkilObjectOrNull(const ePlayerSkillType eSkillType);

	private:
		void fillAnimInfo(SkillAnimationInfo& animInfo, const float width, const float height, const float mag, const UINT spriteCount, const float animDuration);
	
	private:
		PlayerSkillManager()
			: mpPlayerScript(nullptr)
		{

		}
		~PlayerSkillManager() = default;

	private:
		PlayerScript* mpPlayerScript;
	};
}