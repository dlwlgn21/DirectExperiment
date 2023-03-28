#include "jhMaterial.h"
#include "jhShader.h"
#include "jhTexture.h"
#include "jhConstantBuffer.h"


#include "jhPaintShader.h"
#include "jhTime.h"

using namespace jh::graphics;

namespace jh
{
	Material::Material()
		: Resource(eResourceType::METERIAL)
		, mpShader(nullptr)
		, mMaterialConstantBuffer{}
		, mpTexture(nullptr)
		, meRenderingMode(eRenderingMode::OPAQUEE)

		// Added Part At 0327
		//, mpComputeShader(nullptr)
		//, mAccum(0.0f)
	{
		ZeroMemory(&mMaterialConstantBuffer, sizeof(MaterialConstantBuffer));
	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{

		return S_OK;
	}

	void Material::SetDataAtConstantBuffer(const eGPUPrameterType eGPUParamType, void* pData)
	{
		switch (eGPUParamType)
		{
		case eGPUPrameterType::FLOAT:
			mMaterialConstantBuffer.fData = *static_cast<float*>(pData);
			break;
		default:
			assert(false);
			break;
		}
	}
	void Material::BindConstantBufferAndShaderAndSetTextureSRVAtShader()
	{
		//assert(mpTexture != nullptr);
		if (mpTexture != nullptr)
		{
			
			// 요게 Shader의 texture2D defaultTexture : register(t0)로 연결됨. t0 그르니까 0번 슬롯 이라는 것.
			mpTexture->SetShaderResourceView(eShaderStage::PIXEL_SHADER, 0);
			
		}

		// AddedPART
		ConstantBuffer* pConstantBuffer = renderer::pConstantBuffers[static_cast<UINT>(eConstantBufferType::MATERIAL)];
		assert(pConstantBuffer != nullptr);
		//mAccum += Time::DeltaTime();
		//SetDataAtConstantBuffer(eGPUPrameterType::FLOAT, &mAccum);

		pConstantBuffer->WriteConstantBufferAtGPU(&mMaterialConstantBuffer);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::VERTEX_SHADER);
		pConstantBuffer->SetConstantBufferAtShader(eShaderStage::PIXEL_SHADER);
		
		// AddedPART
		//if (mpComputeShader != nullptr)
		//{
		//	pConstantBuffer->SetConstantBufferAtShader(eShaderStage::COMPUTE_SHADER);
		//	mpComputeShader->SetTarget(mpTexture);
		//	mpComputeShader->OnExcute();
		//	mpTexture->SetShaderResourceView(eShaderStage::PIXEL_SHADER, 0);

		//}
		
		assert(mpShader != nullptr);
		mpShader->SetPrimitiveTopologyAndIASetVertexAndPixelShader();
	}

	void Material::Clear()
	{
		mpTexture->Clear();
		
		// AddedPART
		//if (mpComputeShader != nullptr)
		//{
		//	mpTexture->ClearUnorderdAccessView(0);
		//}
	}


}