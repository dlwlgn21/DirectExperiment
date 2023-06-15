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

		void AddSkillObject(const ePlayerSkillType eSkillType);

		void IncreaseElectricSkillDamage(const ePlayerSkillType eSkillType);
		void DecreaseElectricSkillCollTime(const ePlayerSkillType eSkillType);

	private:
		PlayerSkillObject* makePlayerSkilObjectOrNull(const ePlayerSkillType eSkillType);
		void fillAnimInfo(SkillAnimationInfo& animInfo, const float width, const float height, const float mag, const UINT spriteCount, const float animDuration, const std::wstring& animKey);
		void increaseElectricSkillDamage(const ePlayerSkillType eSkillType);
		void decreaseElectricSkillCollTime(const ePlayerSkillType eSkillType);

	private:
		PlayerSkillManager()
			: mpPlayerScript(nullptr)
			, mpPlayerSkillObjects()
		{
			mpPlayerSkillObjects.reserve(static_cast<UINT>(ePlayerSkillType::COUNT));
			mpPlayerSkillObjects.resize(static_cast<UINT>(ePlayerSkillType::COUNT));
		}
		~PlayerSkillManager() = default;

	private:
		PlayerScript* mpPlayerScript;
		std::vector<PlayerSkillObject*>		mpPlayerSkillObjects;
	};
}