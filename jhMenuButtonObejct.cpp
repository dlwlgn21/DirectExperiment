#include "jhMenuButtonObejct.h"
#include "jhSpriteRendererIncludeFiles.h"
#include "jhTransform.h"
#include "jhStartMenuSelectBoxScript.h"
#include "jhGameOberMenuSelectBoxScript.h"

using namespace jh::math;

static constexpr const float BOTH_BUTTON_X_POS = 0.0f;

static constexpr const float START_BUTTON_Y_POS = 0.0f;
static constexpr const float EXIT_BUTTON_Y_POS = -1.0f;

static constexpr const float BOTH_BUTTON_Z_VALUE = 1.1f;
static constexpr const float SELECT_BUTTON_Z_VALUE = 1.0f;

static constexpr const float BOTH_BUTTON_SCALE_VALUE = 2.0f;

namespace jh
{
	MenuButtonObejct::MenuButtonObejct(const eMenuButtonType eType)
		: GameObject()
	{
		setRenderer(eType);
		setTransform(eType);
		if (eType == eMenuButtonType::START_SELECT_BOX)
		{
			MenuSelectBoxScript* pScript = new StartMenuSelectBoxScrip();
			this->AddScript(pScript);
			return;
		}
		if (eType == eMenuButtonType::GAME_OVER_SELECT_BOX)
		{
			MenuSelectBoxScript* pScript = new GameOberMenuSelectBoxScript();
			this->AddScript(pScript);
		}
	}

	void MenuButtonObejct::setRenderer(const eMenuButtonType eType)
	{
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::RECT_MESH_KEY);
		Material* pMaterial = nullptr;
		switch (eType)
		{
		case eMenuButtonType::START:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MATERIAL_START_BUTTON_KEY);
			break;
		}
		case eMenuButtonType::QUIT:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MATERIAL_QUIT_BUTTON_KEY);
			break;
		}
		case eMenuButtonType::RESTART:
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MATERIAL_NEW_GAME_BUTTON_KEY);
			break;
		}
		case eMenuButtonType::START_SELECT_BOX:
		case eMenuButtonType::GAME_OVER_SELECT_BOX:
		/* INTENTIONAL FALL THROUGH */
		{
			pMaterial = ResourcesManager::Find<Material>(ResourceMaker::UI_MATERIAL_SELECT_BUTTON_KEY);
			break;
		}
		default:
			assert(false);
			break;
		}
		SpriteRenderer* pSpriteRenderer = new SpriteRenderer(pMesh, pMaterial);
		this->AddComponent(pSpriteRenderer);
	}
	void MenuButtonObejct::setTransform(const eMenuButtonType eType)
	{
		switch (eType)
		{
		case eMenuButtonType::START:
		{
			GetTransform()->SetPosition(Vector3(BOTH_BUTTON_X_POS, START_BUTTON_Y_POS, BOTH_BUTTON_Z_VALUE));
			break;
		}
		case eMenuButtonType::QUIT:
		{
			GetTransform()->SetPosition(Vector3(BOTH_BUTTON_X_POS, EXIT_BUTTON_Y_POS, BOTH_BUTTON_Z_VALUE));
			break;
		}
		case eMenuButtonType::RESTART:
		{
			GetTransform()->SetPosition(Vector3(BOTH_BUTTON_X_POS, START_BUTTON_Y_POS, BOTH_BUTTON_Z_VALUE));
			break;
		}
		case eMenuButtonType::START_SELECT_BOX:
		case eMenuButtonType::GAME_OVER_SELECT_BOX:
		/* INTENTIONAL FALL THROUGH */
		{
			GetTransform()->SetPosition(Vector3(BOTH_BUTTON_X_POS, START_BUTTON_Y_POS, SELECT_BUTTON_Z_VALUE));
			break;
		}
		default:
			assert(false);
			break;
		}
		GetTransform()->SetOnlyXYScale(Vector2(BOTH_BUTTON_SCALE_VALUE, BOTH_BUTTON_SCALE_VALUE - 1));
	}
}