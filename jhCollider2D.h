#pragma once
#include "jhComponent.h"
#include "jhMath.h"

namespace jh
{
	enum class eColliderState
	{
		ACTIVE,
		INACTIVE,
		COUNT
	};
	class Transform;
	class Collider2D final : public Component
	{
	public:
		Collider2D();
		virtual ~Collider2D() = default;

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;


		void SetType(const eColliderShapeType eType)		{ meColliderShapeType = eType; }
		eColliderShapeType GetColliderShapeType() const		{ return meColliderShapeType; }

		void SetSize(const jh::math::Vector2 size)			{ mSize = size; }
		jh::math::Vector2 GetSize() const					{ return mSize; }
		void SetCenter(const jh::math::Vector2 center)		{ mCenterCoordinate = center; }

		bool GetIsUsePhysics() const						{ return mbIsUsePhysics; }
		UINT GetColliderID() const							{ return mUniqueColliderNumber; }
		jh::math::Vector3 GetPosition() const				{ return mPosition; }

		void SetRadius(const float radius)					{ mRadius = radius; }
		float GetRadius() const								{ return mRadius; }

		void SetState(const eColliderState eState)			{ meState = eState; }
		eColliderState GetState() const						{ return meState; }


		void OnCollisionEnter(Collider2D* pOtherCollider);
		void OnCollisionStay(Collider2D* pOtherCollider);
		void OnCollisionExit(Collider2D* pOtherCollider);

		void OnTriggerEnter(Collider2D* pOtherCollider);
		void OnTriggerStay(Collider2D* pOtherCollider);
		void OnTriggerExit(Collider2D* pOtherCollider);

	private:
		static UINT					sTotalColliderCount;
		UINT						mUniqueColliderNumber;
		eColliderShapeType			meColliderShapeType;
		Transform*					mpTransform;

		jh::math::Vector2			mSize;
		jh::math::Vector2			mCenterCoordinate;
		jh::math::Vector3			mPosition;
		float						mRadius;
		bool						mbIsUsePhysics;
		eColliderState				meState;
	};
}

