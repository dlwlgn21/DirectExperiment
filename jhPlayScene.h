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
		void Render() override;
		void Release() override;
	private:
	};
}

