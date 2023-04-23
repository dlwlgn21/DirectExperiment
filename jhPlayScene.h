#pragma once
#include "jhScene.h"

namespace jh
{
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
		void instantiateCameraAndPlayer();
		void instantiateMonsters();
		void instantiateParallaxObjects();
		void instantiateUIObject();
		void instantiateOtherObjects();

	};
}

