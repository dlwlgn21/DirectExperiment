#define _CRT_SECURE_NO_WARNINGS
#include <random>
#include "jhPlayerLevelManager.h"
#include "jhUILevelUPBorderObject.h"
#include "jhUILevelUpScript.h"
#include "jhUISkillIconScript.h"
#include "jhUISkillTextScript.h"
#include "jhPlayerScript.h"

namespace jh
{
	void PlayerLevelManager::Initialize()
	{
#pragma region UI_LEVEL_UP_BORDER
		UILevelUpBorderObject* pBorder = new UILevelUpBorderObject();
		mpUIBorder = pBorder;
		mpUIBorder->Initialize();
		mpUIBorder->SetState(GameObject::eGameObjectState::INACTIVE);
#pragma endregion
#pragma region SKILL_ICON
		for (UINT i = 0; i < static_cast<UINT>(eSkillIconType::COUNT); ++i)
		{
			mpSkillIconObjects[i] = new UISkillIconObject(static_cast<eSkillIconType>(i));
			mpSkillIconObjects[i]->Initialize();
			mpSkillIconObjects[i]->SetState(GameObject::eGameObjectState::INACTIVE);
		}
#pragma endregion
#pragma region SKILL_TEXT
		for (UINT i = 0; i < static_cast<UINT>(eSkillTextType::COUNT); ++i)
		{
			mpSkillTextObjects[i] = new UISKillTextObject(static_cast<eSkillTextType>(i));
			assert(mpSkillTextObjects[i] != nullptr);
			mpSkillTextObjects[i]->Initialize();
			mpSkillTextObjects[i]->SetState(GameObject::eGameObjectState::INACTIVE);
		}
#pragma endregion
	}

	void PlayerLevelManager::SetPlayerScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		mpPlayerScript = pPlayerScript;
	}

	void PlayerLevelManager::SetCameraTransform(Transform* pCameraTransform)
	{
		assert(pCameraTransform != nullptr);
		static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull())->SetCameraTransform(pCameraTransform);
#pragma region SKILL_ICON
		for (UINT i = 0; i < static_cast<UINT>(eSkillIconType::COUNT); ++i)
		{
			assert(mpSkillIconObjects[i] != nullptr);
			static_cast<UILevelUpScript*>(mpSkillIconObjects[i]->GetScriptOrNull())->SetCameraTransform(pCameraTransform);
		}
#pragma endregion
#pragma region SKILL_TEXT
		for (UINT i = 0; i < static_cast<UINT>(eSkillTextType::COUNT); ++i)
		{
			assert(mpSkillTextObjects[i] != nullptr);
			static_cast<UILevelUpScript*>(mpSkillTextObjects[i]->GetScriptOrNull())->SetCameraTransform(pCameraTransform);
		}
#pragma endregion
	}

	void PlayerLevelManager::OnPlayerLevelUP()
	{
		assert(mpPlayerScript != nullptr);
		mpUIBorder->SetState(GameObject::eGameObjectState::ACTIVE);
		static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull())->SetState(eUILevelUpState::ENTERING);

		static constexpr const int SKILL_ICON_MIN_INDEX_NUMBER = static_cast<int>(eSkillIconType::ELECTRIC_BEAM);
		static constexpr const int SKILL_ICON_MAX_INDEX_NUMBER = static_cast<int>(eSkillIconType::COUNT) - 1;
		static constexpr const UINT MAX_CHOICE_COUNT = 3;
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<> skillIconDist(SKILL_ICON_MIN_INDEX_NUMBER, SKILL_ICON_MAX_INDEX_NUMBER);

		UINT selectedSkillIconIndexs[MAX_CHOICE_COUNT];
#pragma region SKILL_ICON
		while (true)
		{
			for (UINT i = 0; i < MAX_CHOICE_COUNT; ++i)
			{
				selectedSkillIconIndexs[i] = skillIconDist(gen);
			}
			if (selectedSkillIconIndexs[0] != selectedSkillIconIndexs[1] &&
				selectedSkillIconIndexs[0] != selectedSkillIconIndexs[2] &&
				selectedSkillIconIndexs[1] != selectedSkillIconIndexs[2])
			{
				break;
			}
		}
		for (UINT i = 0; i < MAX_CHOICE_COUNT; ++i)
		{
			assert(mpSkillIconObjects[selectedSkillIconIndexs[i]] != nullptr);
			mpSkillIconObjects[selectedSkillIconIndexs[i]]->SetState(GameObject::eGameObjectState::ACTIVE);
			UISkillIconScript* pScript = static_cast<UISkillIconScript*>(mpSkillIconObjects[selectedSkillIconIndexs[i]]->GetScriptOrNull());
			assert(pScript != nullptr);
			pScript->SetState(eUILevelUpState::ENTERING);
			pScript->SetSkillIconPosition(static_cast<eSkillPosition>(i));
		}
#pragma endregion

		for (UINT i = 0; i < MAX_CHOICE_COUNT; ++i)
		{
			const eSkillIconType eSkillType = static_cast<eSkillIconType>(selectedSkillIconIndexs[i]);
			const PlayerScript::PlayerSkillStat& playerSkillStat = mpPlayerScript->GetPlayerSkillStat();
			switch (eSkillType)
			{
			case eSkillIconType::ELECTRIC_BEAM:
			{
				if (playerSkillStat.ElectricBeamLevel.CurrElectricBeamLevel == 0)
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_BEAM_LV_1);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_BEAM_LV_1);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_BEAM_LV_1, eSkillIconType::ELECTRIC_BEAM);
				}
				else
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_DAMAGE, eSkillIconType::ELECTRIC_BEAM);
				}
				break;
			}
			case eSkillIconType::ELECTRIC_STRIKE:
			{
				if (playerSkillStat.ElectricStrikeLevel.CurrElectricStrikeLevel == 0)
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_STRKIE_LV_1);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_STRKIE_LV_1);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_STRKIE_LV_1, eSkillIconType::ELECTRIC_STRIKE);
				}
				else
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_DAMAGE, eSkillIconType::ELECTRIC_STRIKE);
				}
				break;
			}
			case eSkillIconType::ELECTRIC_TORNADO:
			{
				if (playerSkillStat.ElectricTornadoLevel.CurrElectricTornadoLevel == 0)
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_TORNADO_LV_1);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_TORNADO_LV_1);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_TORNADO_LV_1, eSkillIconType::ELECTRIC_TORNADO);
				}
				else
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_SPAWN_SPEED);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_SPAWN_SPEED);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_SPAWN_SPEED, eSkillIconType::ELECTRIC_TORNADO);
				}
				break;
			}
			case eSkillIconType::MELLE_ATTACK_DAMAGE:
			{
				setSkillTextObjectStateToActive(eSkillTextType::SWORD_DAMAGE);
				setSkillTextStateToEntering(eSkillTextType::SWORD_DAMAGE);
				setSkillTextPositionToSkillIconPostion(eSkillTextType::SWORD_DAMAGE, eSkillIconType::MELLE_ATTACK_DAMAGE);
				break;
			}
			case eSkillIconType::SPEED:
			{
				setSkillTextObjectStateToActive(eSkillTextType::MOVEMENT_SPEED);
				setSkillTextStateToEntering(eSkillTextType::MOVEMENT_SPEED);
				setSkillTextPositionToSkillIconPostion(eSkillTextType::MOVEMENT_SPEED, eSkillIconType::SPEED);
				break;
			}
			case eSkillIconType::HEALTH:
			{
				setSkillTextObjectStateToActive(eSkillTextType::RECORVER_HEALTH);
				setSkillTextStateToEntering(eSkillTextType::RECORVER_HEALTH);
				setSkillTextPositionToSkillIconPostion(eSkillTextType::RECORVER_HEALTH, eSkillIconType::HEALTH);
				break;
			}
			default:
				assert(false);
				break;
			}
		}
	}

#pragma region SET_SKILL_TEXT
	void PlayerLevelManager::setSkillTextObjectStateToActive(const eSkillTextType eTextType)
	{
		mpSkillTextObjects[static_cast<UINT>(eTextType)]->SetState(GameObject::eGameObjectState::ACTIVE);
	}
	void PlayerLevelManager::setSkillTextStateToEntering(const eSkillTextType eTextType)
	{
		static_cast<UILevelUpScript*>(mpSkillTextObjects[static_cast<UINT>(eTextType)]->GetScriptOrNull())->SetState(eUILevelUpState::ENTERING);
	}
	void PlayerLevelManager::setSkillTextPositionToSkillIconPostion(const eSkillTextType eTextType, const eSkillIconType eIconType)
	{
		static_cast<UISkillTextScript*>(mpSkillTextObjects[static_cast<UINT>(eTextType)]->GetScriptOrNull())->SetSkillIconPosition(static_cast<UISkillIconScript*>(mpSkillIconObjects[static_cast<UINT>(eIconType)]->GetScriptOrNull())->GetSkillPosition());
	}
#pragma endregion


}