#pragma once
#include "jhEngine.h"
#include "jhUISkillIconObject.h"

namespace jh
{
	class UILevelUpBorderObject;
	class UISkillIconObject;
	class Transform;
	class PlayerLevelManager final
	{
	public:
		static PlayerLevelManager& GetInstance()
		{
			static PlayerLevelManager instance;
			return instance;
		}
		PlayerLevelManager(const PlayerLevelManager& other) = delete;
		PlayerLevelManager& operator=(const PlayerLevelManager& other) = delete;


		void SetCameraTransform(Transform*	pCameraTransform);
		void Initialize();
		void OnPlayerLevelUP();

		UILevelUpBorderObject* GetUIBorder() { assert(mpUIBorder != nullptr); return mpUIBorder; }
		std::vector<UISkillIconObject*>& GetUISkillIcons() { return mpSkillIconObjects; }

	private:
		PlayerLevelManager()
			: mpUIBorder(nullptr)
			, mpSkillIconObjects()
		{
			mpSkillIconObjects.reserve(static_cast<UINT>(eSkillIconType::COUNT));
			mpSkillIconObjects.resize(static_cast<UINT>(eSkillIconType::COUNT));
		}
		~PlayerLevelManager() = default;

	private:
		UILevelUpBorderObject* mpUIBorder;
		std::vector<UISkillIconObject*> mpSkillIconObjects;
	};
}

