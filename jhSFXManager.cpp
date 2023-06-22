#include "jhSFXManager.h"
#include "jhAudioSource.h"
#include "jhSceneManager.h"
#include "jhPlayScene.h"

namespace jh
{
	void SFXManager::Initialize()
	{
		PlayScene* pPlayScene = static_cast<PlayScene*>(SceneManager::GetInstance().GetCurrentScene());
		assert(pPlayScene != nullptr);
		pPlayScene->AddSFXObject(eSFXType::BGM);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_SWING_ATTACK_1);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_SWING_ATTACK_2);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_SWING_ATTACK_3);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_HITTED_1);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_HITTED_2);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_DASH);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_ROLLING);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_FOOTSTEP);
		pPlayScene->AddSFXObject(eSFXType::PLAYER_LEVEL_UP);

		pPlayScene->AddSFXObject(eSFXType::MONSTER_HITTED);
		pPlayScene->AddSFXObject(eSFXType::MONSTER_DIE);
		pPlayScene->AddSFXObject(eSFXType::MONSTER_SPAWN);
		pPlayScene->AddSFXObject(eSFXType::MONSTER_SWING_1);
		pPlayScene->AddSFXObject(eSFXType::MONSTER_SWING_2);
		pPlayScene->AddSFXObject(eSFXType::MONSTER_SWING_3);
		pPlayScene->AddSFXObject(eSFXType::MONSTER_ERUPTION);



		pPlayScene->AddSFXObject(eSFXType::BOSS_MONSTER_FISTING);
		pPlayScene->AddSFXObject(eSFXType::BOSS_MONSTER_SWING);
		pPlayScene->AddSFXObject(eSFXType::BOSS_MONSTER_ERUPTION);
		pPlayScene->AddSFXObject(eSFXType::BOSS_MONSTER_POWER_ERUPTION);
		pPlayScene->AddSFXObject(eSFXType::BOSS_MONSTER_BUFF);
		pPlayScene->AddSFXObject(eSFXType::BOSS_MONSTER_DIE);


		pPlayScene->AddSFXObject(eSFXType::UI_LEVEL_UP_MOVING);
		pPlayScene->AddSFXObject(eSFXType::UI_LEVEL_UP_CHOICE);

		pPlayScene->AddSFXObject(eSFXType::SKILL_BEAM);
		pPlayScene->AddSFXObject(eSFXType::SKILL_STRIKE);
		pPlayScene->AddSFXObject(eSFXType::SKILL_PUSH);
	}
	void SFXManager::Play(const eSFXType eType)
	{
		assert(mpAudioSources[static_cast<UINT>(eType)] != nullptr);
		mpAudioSources[static_cast<UINT>(eType)]->Play();
	}

	void SFXManager::Stop(const eSFXType eType)
	{
		assert(mpAudioSources[static_cast<UINT>(eType)] != nullptr);
		mpAudioSources[static_cast<UINT>(eType)]->Stop();
	}


	void SFXManager::SetAudioSource(const eSFXType eType, AudioSource* pAudioSource)
	{
		assert(mpAudioSources[static_cast<UINT>(eType)] == nullptr && pAudioSource != nullptr);
		mpAudioSources[static_cast<UINT>(eType)] = pAudioSource;
	}
}