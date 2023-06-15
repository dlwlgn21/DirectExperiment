#pragma once
#include "jhEngine.h"
#include "jhUISkillIconObject.h"
#include "jhUISkillTextObject.h"
#include "jhUILevelUpScript.h"

namespace jh
{
	class UILevelUpBorderObject;
	class Transform;
	class PlayerScript;
	class UISkillSelectBoxObject;
	
	struct SampledSkillInfo
	{
		eSkillIconType eSkillIcon;
		eSkillTextType eSkillText;
		eSkillPosition ePosition;
	};

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
		void OnPlayerSelected(const eSkillPosition eSelectedPostion);


		UISkillSelectBoxObject*				GetSkillSelectBox() { assert(mpSKillSelectBox); return mpSKillSelectBox; }
		UILevelUpBorderObject*				GetUIBorder()		{ assert(mpUIBorder != nullptr); return mpUIBorder; }
		std::vector<UISkillIconObject*>&	GetUISkillIcons()	{ return mpSkillIconObjects; }
		std::vector<UISKillTextObject*>&	GetUISkillTexts()	{ return mpSkillTextObjects; }



	private:
		void setSkillTextObjectStateToActive(const eSkillTextType eTextType);
		void setSkillTextStateToEntering(const eSkillTextType eTextType);
		void setSkillTextPositionToSkillIconPostion(const eSkillTextType eTextType, const eSkillIconType eIconType);
		void setSampledSkillInfo(const eSkillIconType eSkillIcon, const eSkillTextType eSkillText, const eSkillPosition ePosition);

		void setPlayerSkillLevel(const eSkillIconType eSkillIcon, const eSkillTextType eSkillText);

	private:
		PlayerLevelManager()
			: mpPlayerScript(nullptr)
			, mpUIBorder(nullptr)
			, mpSKillSelectBox(nullptr)
			, mpSkillIconObjects()
			, mpSkillTextObjects()
			, mSampledThreeSkillInfo{}
		{
			mpSkillIconObjects.reserve(static_cast<UINT>(eSkillIconType::COUNT));
			mpSkillIconObjects.resize(static_cast<UINT>(eSkillIconType::COUNT));
			mpSkillTextObjects.reserve(static_cast<UINT>(eSkillTextType::COUNT));
			mpSkillTextObjects.resize(static_cast<UINT>(eSkillTextType::COUNT));
		}
		~PlayerLevelManager() = default;

	private:
		PlayerScript*						mpPlayerScript;
		UILevelUpBorderObject*				mpUIBorder;
		UISkillSelectBoxObject*				mpSKillSelectBox;
		std::vector<UISkillIconObject*>		mpSkillIconObjects;
		std::vector<UISKillTextObject*>		mpSkillTextObjects;
		SampledSkillInfo					mSampledThreeSkillInfo[3];
	};
}

