#pragma once
#include "jhEngine.h"
#include "jhUISkillIconObject.h"
#include "jhUISkillTextObject.h"

namespace jh
{
	class UILevelUpBorderObject;
	class Transform;
	class PlayerScript;
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

		void SetPlayerScript(PlayerScript* pPlayerScript);
		void SetCameraTransform(Transform*	pCameraTransform);
		void Initialize();
		void OnPlayerLevelUP();

		UILevelUpBorderObject* GetUIBorder() { assert(mpUIBorder != nullptr); return mpUIBorder; }
		std::vector<UISkillIconObject*>& GetUISkillIcons() { return mpSkillIconObjects; }
		std::vector<UISKillTextObject*>& GetUISkillTexts() { return mpSkillTextObjects; }

	private:
		void setSkillTextObjectStateToActive(const eSkillTextType eTextType);
		void setSkillTextStateToEntering(const eSkillTextType eTextType);
		void setSkillTextPositionToSkillIconPostion(const eSkillTextType eTextType, const eSkillIconType eIconType);
	private:
		PlayerLevelManager()
			: mpUIBorder(nullptr)
			, mpPlayerScript(nullptr)
			, mpSkillIconObjects()
			, mpSkillTextObjects()
		{
			mpSkillIconObjects.reserve(static_cast<UINT>(eSkillIconType::COUNT));
			mpSkillIconObjects.resize(static_cast<UINT>(eSkillIconType::COUNT));
			mpSkillTextObjects.reserve(static_cast<UINT>(eSkillTextType::COUNT));
			mpSkillTextObjects.resize(static_cast<UINT>(eSkillTextType::COUNT));
		}
		~PlayerLevelManager() = default;

	private:
		PlayerScript*					mpPlayerScript;
		UILevelUpBorderObject*			mpUIBorder;
		std::vector<UISkillIconObject*> mpSkillIconObjects;
		std::vector<UISKillTextObject*> mpSkillTextObjects;
	};
}

