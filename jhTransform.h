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

		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;

		void WriteMatrixDataAtContantBuffer();
		void SetPipeline();


		__forceinline void SetPosition(const jh::math::Vector3 pos)			{ mPosition = pos; }
		__forceinline void SetRotation(const jh::math::Vector3 rotation)	{ mRotation = rotation; }
		__forceinline void SetScale(const jh::math::Vector3 scale)			{ mScale = scale; }
		void SetParent(GameObject* pGameObject) { assert(pGameObject != nullptr); mpParent = pGameObject->GetTransform(); }

		__forceinline jh::math::Vector3 GetPosition() const { return mPosition; }
		__forceinline jh::math::Vector3 GetRotation() const { return mRotation; }
		__forceinline jh::math::Vector3 GetScale()	  const	{ return mScale; }

		__forceinline jh::math::Vector3 GetForward() const	{ return mForwardVector; }
		__forceinline jh::math::Vector3 GetRight()   const	{ return mRightVector; }
		__forceinline jh::math::Vector3 GetUp()	     const	{ return mUpVector; }


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

