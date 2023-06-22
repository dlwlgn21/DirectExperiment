#define _CRT_SECURE_NO_WARNINGS
#include <random>
#include "jhPlayerLevelManager.h"
#include "jhUILevelUPBorderObject.h"
#include "jhUISkillScript.h"
#include "jhUISkillIconScript.h"
#include "jhUISkillTextScript.h"
#include "jhPlayerScript.h"
#include "jhUISkillSelectBoxObject.h"
#include "jhPlayerSkillManager.h"
#include "jhSFXManager.h"
namespace jh
{
#pragma region INIT
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
			static_cast<UISkillScript*>(mpSkillIconObjects[i]->GetScriptOrNull())->SetUILevelUpBorderScript(static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull()));
		}
#pragma endregion
#pragma region SKILL_TEXT
		for (UINT i = 0; i < static_cast<UINT>(eSkillTextType::COUNT); ++i)
		{
			mpSkillTextObjects[i] = new UISKillTextObject(static_cast<eSkillTextType>(i));
			assert(mpSkillTextObjects[i] != nullptr);
			mpSkillTextObjects[i]->Initialize();
			mpSkillTextObjects[i]->SetState(GameObject::eGameObjectState::INACTIVE);
			static_cast<UISkillScript*>(mpSkillTextObjects[i]->GetScriptOrNull())->SetUILevelUpBorderScript(static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull()));
		}
#pragma endregion
#pragma region SKILL_SELECT_BOX
		mpSKillSelectBox = new UISkillSelectBoxObject();
		mpSKillSelectBox->Initialize();
		mpSKillSelectBox->SetState(GameObject::eGameObjectState::INACTIVE);
		static_cast<UISkillScript*>(mpSKillSelectBox->GetScriptOrNull())->SetUILevelUpBorderScript(static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull()));
#pragma endregion
	}
#pragma endregion

#pragma region SET_PLAYER_CAMERA
	void PlayerLevelManager::SetPlayerScript(PlayerScript* pPlayerScript)
	{
		assert(pPlayerScript != nullptr);
		mpPlayerScript = pPlayerScript;
	}

	void PlayerLevelManager::SetCameraTransform(Transform* pCameraTransform)
	{
		assert(pCameraTransform != nullptr);
		assert(mpSKillSelectBox != nullptr && mpUIBorder != nullptr);
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
#pragma region SKILL_SELECT_BOX
		static_cast<UILevelUpScript*>(mpSKillSelectBox->GetScriptOrNull())->SetCameraTransform(pCameraTransform);
#pragma endregion
	}
#pragma endregion

#pragma region CALL_BACK
	void PlayerLevelManager::OnPlayerLevelUP()
	{
		SFXManager::GetInstance().Stop(eSFXType::PLAYER_FOOTSTEP);
		mbIsProcessingLevelUp = true;
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

#pragma region SKILL_TEXT
		SampledSkillInfo skillInfo;
		ZeroMemory(&skillInfo, sizeof(SampledSkillInfo));
		for (UINT i = 0; i < MAX_CHOICE_COUNT; ++i)
		{
			const eSkillIconType eSkillType = static_cast<eSkillIconType>(selectedSkillIconIndexs[i]);
			const PlayerScript::PlayerSkillStat& playerSkillStat = mpPlayerScript->GetPlayerSkillStat();
			const eSkillPosition eSkillPos = static_cast<eSkillPosition>(i);
			switch (eSkillType)
			{
			case eSkillIconType::ELECTRIC_BEAM:
			{
				if (!playerSkillStat.ElectricBeamLevel.bIsSpawnBeam)
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_BEAM_LV_1);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_BEAM_LV_1);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_BEAM_LV_1, eSkillIconType::ELECTRIC_BEAM);
					
					setSampledSkillInfo(eSkillIconType::ELECTRIC_BEAM, eSkillTextType::ELECTRIC_BEAM_LV_1, eSkillPos);
				}
				else
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_DAMAGE, eSkillIconType::ELECTRIC_BEAM);
				
					setSampledSkillInfo(eSkillIconType::ELECTRIC_BEAM, eSkillTextType::ELECTRIC_DAMAGE, eSkillPos);
				}
				break;
			}
			case eSkillIconType::ELECTRIC_STRIKE:
			{
				if (!playerSkillStat.ElectricStrikeLevel.bIsSpawnStrike)
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_STRKIE_LV_1);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_STRKIE_LV_1);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_STRKIE_LV_1, eSkillIconType::ELECTRIC_STRIKE);
					
					setSampledSkillInfo(eSkillIconType::ELECTRIC_STRIKE, eSkillTextType::ELECTRIC_STRKIE_LV_1, eSkillPos);
				}
				else
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_DAMAGE);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_DAMAGE, eSkillIconType::ELECTRIC_STRIKE);

					setSampledSkillInfo(eSkillIconType::ELECTRIC_STRIKE, eSkillTextType::ELECTRIC_DAMAGE, eSkillPos);
				}
				break;
			}
			case eSkillIconType::ELECTRIC_TORNADO:
			{
				if (!playerSkillStat.ElectricTornadoLevel.bIsSpawnTornado)
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_TORNADO_LV_1);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_TORNADO_LV_1);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_TORNADO_LV_1, eSkillIconType::ELECTRIC_TORNADO);
				
					setSampledSkillInfo(eSkillIconType::ELECTRIC_TORNADO, eSkillTextType::ELECTRIC_TORNADO_LV_1, eSkillPos);

				}
				else
				{
					setSkillTextObjectStateToActive(eSkillTextType::ELECTRIC_SPAWN_SPEED);
					setSkillTextStateToEntering(eSkillTextType::ELECTRIC_SPAWN_SPEED);
					setSkillTextPositionToSkillIconPostion(eSkillTextType::ELECTRIC_SPAWN_SPEED, eSkillIconType::ELECTRIC_TORNADO);
				
					setSampledSkillInfo(eSkillIconType::ELECTRIC_TORNADO, eSkillTextType::ELECTRIC_SPAWN_SPEED, eSkillPos);
				}
				break;
			}
			case eSkillIconType::MELLE_ATTACK_DAMAGE:
			{
				setSkillTextObjectStateToActive(eSkillTextType::SWORD_DAMAGE);
				setSkillTextStateToEntering(eSkillTextType::SWORD_DAMAGE);
				setSkillTextPositionToSkillIconPostion(eSkillTextType::SWORD_DAMAGE, eSkillIconType::MELLE_ATTACK_DAMAGE);

				setSampledSkillInfo(eSkillIconType::MELLE_ATTACK_DAMAGE, eSkillTextType::SWORD_DAMAGE, eSkillPos);
				break;
			}
			case eSkillIconType::SPEED:
			{
				setSkillTextObjectStateToActive(eSkillTextType::MOVEMENT_SPEED);
				setSkillTextStateToEntering(eSkillTextType::MOVEMENT_SPEED);
				setSkillTextPositionToSkillIconPostion(eSkillTextType::MOVEMENT_SPEED, eSkillIconType::SPEED);
				setSampledSkillInfo(eSkillIconType::SPEED, eSkillTextType::MOVEMENT_SPEED, eSkillPos);
				break;
			}
			case eSkillIconType::HEALTH:
			{
				setSkillTextObjectStateToActive(eSkillTextType::RECORVER_HEALTH);
				setSkillTextStateToEntering(eSkillTextType::RECORVER_HEALTH);
				setSkillTextPositionToSkillIconPostion(eSkillTextType::RECORVER_HEALTH, eSkillIconType::HEALTH);
				setSampledSkillInfo(eSkillIconType::HEALTH, eSkillTextType::RECORVER_HEALTH, eSkillPos);
				break;
			}
			default:
				assert(false);
				break;
			}
		}
#pragma endregion

#pragma region SKILL_SELECT_BOX
		mpSKillSelectBox->SetState(GameObject::eGameObjectState::ACTIVE);
		static_cast<UILevelUpScript*>(mpSKillSelectBox->GetScriptOrNull())->SetState(eUILevelUpState::ENTERING);
#pragma endregion
	}
	void PlayerLevelManager::OnPlayerSelected(const eSkillPosition eSelectedPostion)
	{
		assert(mpPlayerScript != nullptr);
		const eSkillIconType eSmapledSkillIocnType = mSampledThreeSkillInfo[static_cast<UINT>(eSelectedPostion)].eSkillIcon;
		const eSkillTextType eSmapledSkillTextType = mSampledThreeSkillInfo[static_cast<UINT>(eSelectedPostion)].eSkillText;
		setPlayerSkillLevel(eSmapledSkillIocnType, eSmapledSkillTextType);

		setInacitveAllUILevelUpObjects();
		mbIsProcessingLevelUp = false;
		mpPlayerScript->mbIsLevelUping = false;
	}
#pragma endregion

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

#pragma region SET_SAMPLEED_SKILL_INFO
	void PlayerLevelManager::setSampledSkillInfo(const eSkillIconType eSkillIcon, const eSkillTextType eSkillText, const eSkillPosition ePosition)
	{
		mSampledThreeSkillInfo[static_cast<UINT>(ePosition)].eSkillIcon = eSkillIcon;
		mSampledThreeSkillInfo[static_cast<UINT>(ePosition)].eSkillText = eSkillText;
		mSampledThreeSkillInfo[static_cast<UINT>(ePosition)].ePosition = ePosition;
	}

#pragma endregion

#pragma region SET_PLAYER_SKILL_LEVEL
	void PlayerLevelManager::setPlayerSkillLevel(const eSkillIconType eSkillIcon, const eSkillTextType eSkillText)
	{
		switch (eSkillText)
		{
		case jh::eSkillTextType::ELECTRIC_BEAM_LV_1:
		{
			mpPlayerScript->mSkillStat.ElectricBeamLevel.bIsSpawnBeam = true;
			PlayerSkillManager::GetInstance().AddSkillObject(ePlayerSkillType::ELETRIC_BEAM);
			break;
		}
		case jh::eSkillTextType::ELECTRIC_STRKIE_LV_1:
		{
			mpPlayerScript->mSkillStat.ElectricStrikeLevel.bIsSpawnStrike = true;
			PlayerSkillManager::GetInstance().AddSkillObject(ePlayerSkillType::ELETRIC_STRIKE);
			break;
		}
		case jh::eSkillTextType::ELECTRIC_TORNADO_LV_1:
		{
			mpPlayerScript->mSkillStat.ElectricTornadoLevel.bIsSpawnTornado = true;
			PlayerSkillManager::GetInstance().AddSkillObject(ePlayerSkillType::TORNADO);
			break;
		}
		case jh::eSkillTextType::ELECTRIC_DAMAGE:
		{
			switch (eSkillIcon)
			{
			case eSkillIconType::ELECTRIC_BEAM:
			{
				++mpPlayerScript->mSkillStat.ElectricBeamLevel.CurrElectricBeamDamageLevel;
				PlayerSkillManager::GetInstance().IncreaseElectricSkillDamage(ePlayerSkillType::ELETRIC_BEAM);
				break;
			}
			case eSkillIconType::ELECTRIC_STRIKE:
			{
				++mpPlayerScript->mSkillStat.ElectricStrikeLevel.CurrElectricStrikeDamageLevel;
				PlayerSkillManager::GetInstance().IncreaseElectricSkillDamage(ePlayerSkillType::ELETRIC_STRIKE);
				break;
			}
			default:
				assert(false);
				break;
			}
			break;
		}

		case jh::eSkillTextType::ELECTRIC_SPAWN_SPEED:
		{
			switch (eSkillIcon)
			{
			case eSkillIconType::ELECTRIC_BEAM:
			{
				assert(mpPlayerScript->mSkillStat.ElectricBeamLevel.bIsSpawnBeam);
				++mpPlayerScript->mSkillStat.ElectricBeamLevel.CurrElectricBeamSpawnSpeedLevel;
				PlayerSkillManager::GetInstance().DecreaseElectricSkillCollTime(ePlayerSkillType::ELETRIC_BEAM);
				break;
			}
			case eSkillIconType::ELECTRIC_STRIKE:
			{
				assert(mpPlayerScript->mSkillStat.ElectricStrikeLevel.bIsSpawnStrike);
				++mpPlayerScript->mSkillStat.ElectricStrikeLevel.CurrElectricStrikeSpawnSpeedLevel;
				PlayerSkillManager::GetInstance().DecreaseElectricSkillCollTime(ePlayerSkillType::ELETRIC_STRIKE);
				break;
			}
			case eSkillIconType::ELECTRIC_TORNADO:
			{
				assert(mpPlayerScript->mSkillStat.ElectricTornadoLevel.bIsSpawnTornado);
				++mpPlayerScript->mSkillStat.ElectricTornadoLevel.CurrElectricTornadoSpawnSpeedLevel;
				PlayerSkillManager::GetInstance().DecreaseElectricSkillCollTime(ePlayerSkillType::TORNADO);
				break;
			}
			default:
				assert(false);
				break;
			}
			break;
		}
		case jh::eSkillTextType::SWORD_DAMAGE:
		{
			++mpPlayerScript->mSkillStat.CurrSwordLevel;
			break;
		}
		case jh::eSkillTextType::MOVEMENT_SPEED:
		{
			++mpPlayerScript->mSkillStat.CurrMovementSpeedLevel;
			mpPlayerScript->mSpeed *= 1.1f;
			break;
		}
		case jh::eSkillTextType::RECORVER_HEALTH:
		{
			mpPlayerScript->mStat.CurrentHP = mpPlayerScript->mStat.MaxHP;
			break;
		}
		default:
			assert(false);
			break;
		}
	}

#pragma endregion

	void PlayerLevelManager::setInacitveAllUILevelUpObjects()
	{
		mpUIBorder->SetState(GameObject::eGameObjectState::INACTIVE);
		static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull())->InitWaitingStatePosition();

		mpSKillSelectBox->SetState(GameObject::eGameObjectState::INACTIVE);
		static_cast<UILevelUpScript*>(mpSKillSelectBox->GetScriptOrNull())->InitWaitingStatePosition();

		for (auto* pSkillObject : mpSkillIconObjects)
		{
			pSkillObject->SetState(GameObject::eGameObjectState::INACTIVE);
			static_cast<UILevelUpScript*>(pSkillObject->GetScriptOrNull())->InitWaitingStatePosition();
		}

		for (auto* pSkillTextObject : mpSkillTextObjects)
		{
			pSkillTextObject->SetState(GameObject::eGameObjectState::INACTIVE);
			static_cast<UILevelUpScript*>(pSkillTextObject->GetScriptOrNull())->InitWaitingStatePosition();
		}
	}
}