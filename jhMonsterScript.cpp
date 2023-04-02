#include "jhMonsterScript.h"
#include "jhInput.h"
#include "jhTime.h"

namespace jh
{
	MonsterScript::MonsterScript()
		: Script()
		, mX(0.0f)
		, mY(0.0f)
		, mZ(0.0f)
		, mWorldMat()
		, mcpConstantBuffer()
	{
		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth = sizeof(MatrixBuffer);
		BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		BufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;

		HRESULT hr = graphics::GraphicDeviceDX11::GetInstance().GetDeivce()->CreateBuffer(
			&BufferDesc,
			nullptr,
			mcpConstantBuffer.ReleaseAndGetAddressOf()
		);

		if (FAILED(hr)) { assert(false); }

	}
	MonsterScript::~MonsterScript()
	{
		mcpConstantBuffer.Reset();
	}
	void MonsterScript::Initialize()
	{
	}
	void MonsterScript::Update()
	{
		static const float SPEED = 1.0f;
		if (Input::GetKeyState(eKeyCode::Q) == eKeyState::PRESSED)
		{
			mZ += DirectX::XM_PI * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::E) == eKeyState::PRESSED)
		{
			mZ -= DirectX::XM_PI * Time::DeltaTime();
		}


		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			mX += SPEED * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			mX -= SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			mY -= SPEED * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			mY += SPEED * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::N_1) == eKeyState::PRESSED)
		{
			Time::SetScale(1.0f);
		}
		if (Input::GetKeyState(eKeyCode::N_2) == eKeyState::PRESSED)
		{
			Time::SetScale(2.0f);
		}
		if (Input::GetKeyState(eKeyCode::N_3) == eKeyState::PRESSED)
		{
			Time::SetScale(3.0f);
		}

		mWorldMat = DirectX::XMMatrixIdentity();
		mWorldMat *= DirectX::XMMatrixRotationZ(mZ);
		mWorldMat *= DirectX::XMMatrixTranslation(mX, mY, 0.0f);
	}
	void MonsterScript::FixedUpdate()
	{
		MatrixBuffer matBuffer;
		matBuffer.worldMat = DirectX::XMMatrixTranspose(mWorldMat);
		graphics::GraphicDeviceDX11::GetInstance().WriteDataAtBuffer(mcpConstantBuffer.Get(), &matBuffer, sizeof(MatrixBuffer));
	}
	void MonsterScript::Render()
	{
		setPipeline();
	}
	void MonsterScript::setPipeline()
	{
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->VSSetConstantBuffers(
			0,
			1,
			mcpConstantBuffer.GetAddressOf()
		);
	}
}