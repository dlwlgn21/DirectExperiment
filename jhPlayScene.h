#pragma once
#include "jhScene.h"

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

	private:
		PlayerScript* instantiateCameraAndPlayer();
		void instantiateMonsters(PlayerScript* pPlayerScript);
		void instantiateParallaxObjects();
		void instantiateEnvObject();
		void instantiateUIObject(PlayerScript* pPlayerScript);
		void instantiateOtherObjects();

	};
}

