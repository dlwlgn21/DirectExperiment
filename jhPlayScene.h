#pragma once
#include "jhScene.h"
#include "jhMonsterManager.h"
#include "jhBGTreeObject.h"

namespace jh
{
	class PlayerScript;
	class PlayScene final : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();


		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Release() override;

		void AddMonster(const MonsterPackage& monPack);

	private:
		void instantiateLight(PlayerScript* pPlayerScript);
		PlayerScript* instantiateCameraAndPlayer();
		void instantiateMonsters(PlayerScript* pPlayerScript);
		void instantiateParallaxObjects();
		void instantiateEnvObject();
		void instatiateTreeObejct();
		void instatiateLightningObejct();
		void instantiateUIObject(PlayerScript* pPlayerScript);
		void instantiateOtherObjects();
		void instantiateEnvTreeObject(const float xPos, const eTreeShapeType eTreeType, const eTreeAnimType eAnimType);

	};
}

