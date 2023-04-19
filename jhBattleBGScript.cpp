#include "jhBattleBGScript.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhResourceMaker.h"
#include "jhTransform.h"

using namespace jh::math;

static constexpr const float BATTLE_BG_Z_VALUE = 10.0f;
static constexpr const float BATTLE_PARRALL_BG_Z_VALUE = 11.0f;

namespace jh
{
	BattleBGScript::BattleBGScript(const eBGType eType)
		: Script()
		, mSpeed(0.1f)
		, mUVMove(Vector2::Zero)
		, meType(eType)
	{
	}
	void BattleBGScript::Initialize()
	{
		Transform* pTransform = GetOwner()->GetTransform();
		Vector3 prePos = pTransform->GetPosition();

		switch (meType)
		{
		case jh::eBGType::NORMAL:
			mSpeed = 0.1f;
			pTransform->SetPosition(Vector3(prePos.x, prePos.y, BATTLE_BG_Z_VALUE));
			break;
		case jh::eBGType::PARRARELL:
			mSpeed = 0.1f;
			pTransform->SetPosition(Vector3(prePos.x, prePos.y, BATTLE_PARRALL_BG_Z_VALUE));
			break;
		default:
			assert(false);
			break;
		}
	}
	void BattleBGScript::Update()
	{
		//if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		//{
		//	mUVMove.y -= mSpeed * Time::DeltaTime();
		//}
		//if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		//{
		//	mUVMove.y += mSpeed * Time::DeltaTime();
		//}
		//if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		//{
		//	mUVMove.x -= mSpeed * Time::DeltaTime();
		//}
		//if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		//{
		//	mUVMove.x += mSpeed * Time::DeltaTime();
		//}

	}
	void BattleBGScript::FixedUpdate()
	{
		wirteDataAtBuffer();
		setPipeline();
	}
	void BattleBGScript::Render()
	{

	}
	void BattleBGScript::wirteDataAtBuffer()
	{
		UVTranslatationBuffer uvBffer;
		ZeroMemory(&uvBffer, sizeof(UVTranslatationBuffer));
		uvBffer.UVPosition = Vector4(mUVMove.x, mUVMove.y, 0.0f, 0.0f);
		ConstantBuffer* pConstantBuffer = ResourceMaker::GetInstance().GetUVTranslationCBOrNull();
		assert(pConstantBuffer != nullptr);
		pConstantBuffer->WirteDataAtBuffer(pConstantBuffer->GetBuffer(), &uvBffer, sizeof(UVTranslatationBuffer));
	}
	void BattleBGScript::setPipeline()
	{
		ConstantBuffer* pConstantBuffer = ResourceMaker::GetInstance().GetUVTranslationCBOrNull();
		assert(pConstantBuffer != nullptr);
		pConstantBuffer->SetPipeline();
	}
}