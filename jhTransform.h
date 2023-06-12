#pragma once
#include "jhComponent.h"
#include "jhGraphics.h"

namespace jh
{
	class Transform final : public Component
	{
	public:
		Transform();
		virtual ~Transform() = default;

		void FixedUpdate() override;
		void Render() override;

		void WriteMatrixDataAtContantBuffer();
		void SetPipeline();


		__forceinline void SetPosition(const jh::math::Vector3 pos)					{ mPosition = pos; }
		__forceinline void SetOnlyXPosition(const float xPos)						{ mPosition.x = xPos; }
		__forceinline void SetOnlyYPosition(const float yPos)						{ mPosition.y = yPos; }
		__forceinline void SetOnlyYZPosition(const float yPos, const float zPos)	{ mPosition.y = yPos;  mPosition.z = zPos; }
		
		
		__forceinline void SetOnlyXYPosition(const float xPos, const float yPos)	{ mPosition.x = xPos; mPosition.y = yPos; }
		__forceinline void SetOnlyXYPosition(const jh::math::Vector2 pos)	{ mPosition.x = pos.x; mPosition.y = pos.y; }
		__forceinline void SetRotation(const jh::math::Vector3 rotation)			{ mRotation = rotation; }

		__forceinline void SetOnlyXScale(const float xSclae)						{ mScale.x = xSclae; }
		__forceinline void SetOnlyXYScale(const float xScale, const float yScale)	{ mScale.x = xScale; mScale.y = yScale; }
		__forceinline void SetOnlyXYScale(const float xAndyScale)	{ mScale.x = xAndyScale; mScale.y = xAndyScale; }
		__forceinline void SetScale(const jh::math::Vector3 scale)					{ mScale = scale; }
		void SetParent(GameObject* pGameObject) { assert(pGameObject != nullptr); mpParent = pGameObject->GetTransform(); }

		__forceinline jh::math::Vector3 GetPosition() const			{ return mPosition; }
		__forceinline float GetOnlyXPosition()		  const			{ return mPosition.x; }
		__forceinline float GetOnlyYPosition()		  const			{ return mPosition.y; }
		__forceinline jh::math::Vector2 GetOnlyXYPosition() const	{ return jh::math::Vector2(mPosition.x, mPosition.y); }
		__forceinline jh::math::Vector3 GetRotation() const			{ return mRotation; }
		__forceinline jh::math::Vector3 GetScale()	  const			{ return mScale; }

		__forceinline jh::math::Vector3 GetForward() const			{ return mForwardVector; }
		__forceinline jh::math::Vector3 GetRight()   const			{ return mRightVector; }
		__forceinline jh::math::Vector3 GetUp()	     const			{ return mUpVector; }


		const jh::math::Matrix& GetWorldMatrix() { return mWolrdMat; }

	private:
		Transform*				mpParent;

		jh::math::Vector3		mForwardVector;
		jh::math::Vector3		mRightVector;
		jh::math::Vector3		mUpVector;

		jh::math::Vector3		mPosition;
		jh::math::Vector3		mRotation;
		jh::math::Vector3		mScale;

		jh::math::Matrix		mWolrdMat;
	};
}

