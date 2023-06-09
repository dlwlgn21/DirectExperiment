#include "jhTransform.h"
#include "jhGraphicDeviceDX11.h"
#include "jhConstantBuffer.h"
#include "jhResourceMaker.h"
#include "jhCamera.h"

using namespace jh::math;

namespace jh
{
	Transform::Transform()
		: Component(eComponentType::TRANSFORM)
		, mpParent(nullptr)
		, mForwardVector(Vector3::Forward)
		, mRightVector(Vector3::Right)
		, mUpVector(Vector3::Up)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mWolrdMat()
	{
	
	}

	void Transform::FixedUpdate()
	{
		// Update Transform data for Rendering object
		// Create WorldMatrix
		Matrix scaleMat = Matrix::CreateScale(mScale);

		Matrix rotationMat;
		rotationMat = Matrix::CreateRotationX(mRotation.x);
		rotationMat *= Matrix::CreateRotationY(mRotation.y);
		rotationMat *= Matrix::CreateRotationZ(mRotation.z);

		Matrix translationMat;
		translationMat.Translation(mPosition);

		mWolrdMat = scaleMat * rotationMat * translationMat;

		mForwardVector = Vector3::TransformNormal(Vector3::Forward, rotationMat);
		mRightVector = Vector3::TransformNormal(Vector3::Right, rotationMat);
		mUpVector = Vector3::TransformNormal(Vector3::Up, rotationMat);

		if (mpParent != nullptr)
		{
			mWolrdMat *= mpParent->mWolrdMat;
		}
	}

	void Transform::Render()
	{
	}
	void Transform::WriteMatrixDataAtContantBuffer()
	{
		TransformBuffer buffer;
		ZeroMemory(&buffer, sizeof(TransformBuffer));
		buffer.WorldMat =		mWolrdMat;
		buffer.ViewMat =		Camera::GetGpuViewMatrix();
		buffer.ProjectionMat =	Camera::GetGpuProjectionMatrix();

		ConstantBuffer* pTrCB = ResourceMaker::GetInstance().GetTransformCBOrNull();
		assert(pTrCB != nullptr);
		pTrCB->WirteDataAtBuffer(pTrCB->GetBuffer(), &buffer, sizeof(TransformBuffer));
	}

	void Transform::SetPipeline()
	{
		ConstantBuffer* pTrCB = ResourceMaker::GetInstance().GetTransformCBOrNull();
		assert(pTrCB != nullptr);
		pTrCB->SetPipeline();
	}
}