#pragma once
#include "jhGameObject.h"
#include "jhSpriteRenderer.h"
#include "jhResourceMaker.h"
#include "jhResourcesManager.h"
#include "jhMaterial.h"
#include "jhMesh.h"
#include "jhBattleBGScript.h"


namespace jh
{
	class BattleParrarellImageObject final : public GameObject
	{
	public:
		BattleParrarellImageObject();
		virtual ~BattleParrarellImageObject() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

	private:
		void setRenderer();
		void setScript();
	};
}



