#include "jhPlayerLevelManager.h"
#include "jhUILevelUPBorderObject.h"
#include "jhUILevelUpScript.h"
#include "jhSceneManager.h"
#include "jhScene.h"

namespace jh
{
	void PlayerLevelManager::Initialize()
	{
		UILevelUpBorderObject* pBorder = new UILevelUpBorderObject();
		mpUIBorder = pBorder;
		mpUIBorder->Initialize();
		mpUIBorder->SetState(GameObject::eGameObjectState::INACTIVE);
		for (UINT i = 0; i < static_cast<UINT>(eSkillIconType::COUNT); ++i)
		{
			mpSkillIconObjects[i] = new UISkillIconObject(static_cast<eSkillIconType>(i));
			mpSkillIconObjects[i]->Initialize();
			mpSkillIconObjects[i]->SetState(GameObject::eGameObjectState::INACTIVE);
		}
	}

	void PlayerLevelManager::SetCameraTransform(Transform* pCameraTransform)
	{
		assert(pCameraTransform != nullptr);
		static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull())->SetCameraTransform(pCameraTransform);
		for (UINT i = 0; i < static_cast<UINT>(eSkillIconType::COUNT); ++i)
		{
			assert(mpSkillIconObjects[i] != nullptr);
			static_cast<UILevelUpScript*>(mpSkillIconObjects[i]->GetScriptOrNull())->SetCameraTransform(pCameraTransform);
		}
	}

	void PlayerLevelManager::OnPlayerLevelUP()
	{
		mpUIBorder->SetState(GameObject::eGameObjectState::ACTIVE);
		static_cast<UILevelUpScript*>(mpUIBorder->GetScriptOrNull())->SetState(eUILevelUpState::ENTERING);
		for (UINT i = 0; i < static_cast<UINT>(eSkillIconType::COUNT); ++i)
		{
			assert(mpSkillIconObjects[i] != nullptr);
			mpSkillIconObjects[i]->SetState(GameObject::eGameObjectState::ACTIVE);
			static_cast<UILevelUpScript*>(mpSkillIconObjects[i]->GetScriptOrNull())->SetState(eUILevelUpState::ENTERING);
		}
	}
}