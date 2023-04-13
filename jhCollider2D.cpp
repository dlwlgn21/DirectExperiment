#include "jhCollider2D.h"
#include "jhGameObject.h"
#include "jhTransform.h"
#include "jhScript.h"
#include "jhGraphics.h"
#include "jhResourceMaker.h"

using namespace jh::math;

namespace jh
{
	UINT Collider2D::sTotalColliderCount = 0;

	Collider2D::Collider2D()
		: Component(eComponentType::COLLIDER)
		, meColliderShapeType(eColliderShapeType::RECT)
		, mpTransform(nullptr)
		, mRadius(0.0f)
		, mSize(Vector2::One)
		, mCenterCoordinate(Vector2::Zero)
		, mPosition(Vector2::Zero)
		, mbIsUsePhysics(false)
		, mUniqueColliderNumber(sTotalColliderCount++)
	{
	}

	void Collider2D::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
	}


	void Collider2D::Update()
	{
	}


	void Collider2D::FixedUpdate()
	{
		Vector3 scale = mpTransform->GetScale();
		scale *= Vector3(mSize.x, mSize.y, 1.0f);

		Vector3 rotation = mpTransform->GetRotation();

		Vector3 position = mpTransform->GetPosition();
		Vector3 colliderPosition = position + Vector3(mCenterCoordinate.x, mCenterCoordinate.y, 0.0f);
		mPosition = colliderPosition;


		// Make World Transform Matrix
		Matrix scaleMat = Matrix::CreateScale(scale);
		Matrix rotationMat;
		rotationMat = Matrix::CreateRotationX(rotation.x);
		rotationMat *= Matrix::CreateRotationY(rotation.y);
		rotationMat *= Matrix::CreateRotationZ(rotation.z);

		Matrix translationMat;
		translationMat.Translation(Vector3(mPosition.x, mPosition.y, mPosition.z));

		Matrix worldMat = scaleMat * rotationMat * translationMat;

		DebugMesh debugMesh;
		ZeroMemory(&debugMesh, sizeof(DebugMesh));
		debugMesh.Scale = scale;
		debugMesh.Rotation = rotation;
		debugMesh.Position = Vector3(mPosition.x, mPosition.y, mPosition.z);
		debugMesh.Radius = mRadius;
		debugMesh.EColiiderShapeType = meColliderShapeType;
		ResourceMaker::GetInstance().PushBackDebugMesh(debugMesh);
	}


	void Collider2D::Render()
	{
	}


	void Collider2D::OnCollisionEnter(Collider2D* pOtherCollider)
	{
		auto& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			pScript->OnCollisionEnter(pOtherCollider);
		}
	}


	void Collider2D::OnCollisionStay(Collider2D* pOtherCollider)
	{
		auto& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			pScript->OnCollisionStay(pOtherCollider);
		}
	}


	void Collider2D::OnCollisionExit(Collider2D* pOtherCollider)
	{
		auto& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			pScript->OnCollisionExit(pOtherCollider);
		}
	}


	void Collider2D::OnTriggerEnter(Collider2D* pOtherCollider)
	{
		auto& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			pScript->OnTriggerEnter(pOtherCollider);
		}
	}


	void Collider2D::OnTriggerStay(Collider2D* pOtherCollider)
	{
		auto& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			pScript->OnTriggerStay(pOtherCollider);
		}
	}


	void Collider2D::OnTriggerExit(Collider2D* pOtherCollider)
	{
		auto& scripts = GetOwner()->GetScripts();
		for (auto* pScript : scripts)
		{
			pScript->OnTriggerExit(pOtherCollider);
		}
	}
}