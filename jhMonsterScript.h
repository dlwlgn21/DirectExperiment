#pragma once
#include "jhScript.h"
#include "jhGraphicDeviceDX11.h"

namespace jh
{
	class MonsterScript final : public Script
	{
	public:
		MonsterScript();
		virtual ~MonsterScript();

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;


	private:
		void setPipeline();

	private:
		float mX;
		float mY;
		float mZ;
		DirectX::XMMATRIX mWorldMat;
		Microsoft::WRL::ComPtr<ID3D11Buffer>			mcpConstantBuffer;
	};
}

