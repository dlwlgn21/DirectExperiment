#pragma once
#include "jhScene.h"
#include "jhMonsterManager.h"
#include "jhBGTreeObject.h"
#include "jhGraphics.h"
#include "jhSFXEnum.h"

namespace jh
{
	class Transform;
	class PlayerScript;
	class ProtectingCrystalScript;
	class PlayScene final : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene() = default;


		void Initialize() override;
		void Update() override;
		//void FixedUpdate() override;
		void AddMonster(const MonsterPackage& monPack);
		void AddBossMonster(AcientBossMonsterPackage& monPack);
		void AddSkillObejct(GameObject* pGameObject);
		void AddSFXObject(const eSFXType eType);

		void SetIsStartGameTrue()	{ mbIsStartGame = true; }	
		bool IsStartGame() const	{ return mbIsStartGame; }
		void InstantiateUIObject();
		void ChangeCrystalState();
		PlayerScript* GetPlayerScript() { assert(mpPlayerScript != nullptr); return mpPlayerScript; }
		std::vector<GameObject*>& GetUIObjects() { return mpUIObjects; }
	private:
		void instantiateLight(PlayerScript* pPlayerScript);
		PlayerScript* instantiateCameraAndPlayer();
		void instantiateParallaxObjects();
		void instantiateEnvObject();
		void instatiateTreeObejct();
		void instatiateLightningObejct();
		void instantiateEnvTreeObject(const float xPos, const eTreeShapeType eTreeType, const eTreeAnimType eAnimType);
		void instantiateLightObject(const LightAttribute& lightAttribute, const jh::math::Vector2& pos);
		void instantiateLightObject(const LightAttribute& lightAttribute, Transform* pTransform);

	private:
		PlayerScript*				mpPlayerScript;
		ProtectingCrystalScript*	mpCrystalScript;
		bool						mbIsStartGame;
		std::vector<GameObject*>	mpUIObjects;
	};
}

