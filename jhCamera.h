#pragma once
#include "jhComponent.h"
#include "jhGraphics.h"


namespace jh
{
	enum class eProjectionMode
	{
		PERSPECTIVE_MODE,
		ORTHOGRAPHIC_MODE,
		COUNT
	};
	class Camera final : public Component
	{
	public:
		__forceinline static jh::math::Matrix& GetGpuViewMatrix() { return sViewMat; }
		__forceinline static jh::math::Matrix& GetGpuProjectionMatrix() { return sProjectionMat; }
		__forceinline static void SetGpuViewMatrix(jh::math::Matrix viewMat) { sViewMat = viewMat; }
		__forceinline static void SetGpuProjectionMatrix(jh::math::Matrix projectionMat) { sProjectionMat = projectionMat; }

	public:
		Camera();
		virtual ~Camera() = default;
		
		void Initialize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;


		void CreateViewMatrix();
		void CreateProjectionMatrix();

		void SetProjectionMode(const eProjectionMode eMode) { meProjectionMode = eMode; }

		void TurnLayerMask(const eLayerType eLayer, const bool bIsEnable = true);
		void EnableAllLayerMasks() { mLayerMasks.set(); }
		void DisableAllLayerMasks() { mLayerMasks.reset(); }

		float GetScale() const { return mScale; }
		jh::math::Matrix& GetViewMatrix() { return mViewMat; }
		jh::math::Matrix& GetProjectionMatrix() { return mProjectionMat; }



	private:
		static jh::math::Matrix									sViewMat;
		static jh::math::Matrix									sProjectionMat;

		jh::math::Matrix										mViewMat;
		jh::math::Matrix										mProjectionMat;


		eProjectionMode											meProjectionMode;
		float													mAspectRatio;
		
		float													mNearPlain;
		float													mFarPlain;
		float													mScale;

		std::bitset<static_cast<UINT>(eLayerType::COUNT)>		mLayerMasks;
	};
}

