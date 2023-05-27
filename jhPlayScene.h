#pragma once
#include "jhScene.h"
#include "jhMonsterManager.h"

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
		void instantiateUIObject(PlayerScript* pPlayerScript);
		void instantiateOtherObjects();

	};
}

