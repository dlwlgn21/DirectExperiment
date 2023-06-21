#include "jhCamera.h"
#include "jhTransform.h"
#include "jhGameObject.h"
#include "jhD3DApp.h"
#include "jhSceneManager.h"
#include "jhScene.h"
#include "jhRenderer.h"
#include "jhMonsterHPSpriteRenderer.h"

using namespace jh::math;
namespace jh
{
	Matrix Camera::sViewMat = Matrix::Identity;
	Matrix Camera::sProjectionMat = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::CAMERA)
		, mViewMat()
		, mProjectionMat()
		, meProjectionMode(eProjectionMode::PERSPECTIVE_MODE)
		, mAspectRatio(1.0f)
		, mNearPlain(1.0f)
		, mFarPlain(1000.0f)
		, mScale(1.0f)
		, mLayerMasks()
	{
		EnableAllLayerMasks();
	}

	void Camera::Initialize()
	{
	}
	void Camera::Update()
	{
	}
	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();
	}
	void Camera::Render()
	{
		sViewMat = mViewMat;
		sProjectionMat = mProjectionMat;

		Scene* pCurrScene = SceneManager::GetInstance().GetCurrentScene();
		assert(pCurrScene != nullptr);
		for (UINT i = 0; i < static_cast<UINT>(eLayerType::COUNT); ++i)
		{
			if (mLayerMasks[i])
			{
				Layer* pLayer = pCurrScene->GetLayer(static_cast<eLayerType>(i));
				const std::vector<GameObject*>& layerGameObjects = pLayer->GetAllGameObjects();

				if (layerGameObjects.empty())	{continue;}
				
				for (auto* pGameObject : layerGameObjects)
				{
					if (pGameObject == nullptr) {continue;}
					if (pGameObject->GetState() != GameObject::eGameObjectState::ACTIVE) { continue; }
					Renderer* pRenderer = static_cast<Renderer*>(pGameObject->GetComponentOrNull(eComponentType::RENDERER));
					if (pRenderer != nullptr)	
					{ 
						pRenderer->Render(); 
					}
				}
			}
		}
	}

	void Camera::CreateViewMatrix()
	{
		Transform* pTransform = GetOwner()->GetTransform();
		assert(pTransform != nullptr);

		// Translation
		Vector3 position = pTransform->GetPosition();
		mViewMat = Matrix::Identity;
		mViewMat *= Matrix::CreateTranslation(-position);

		// Rotation
		Vector3 upVector = pTransform->GetUp();
		Vector3 rightVector = pTransform->GetRight();
		Vector3 forwardVector = pTransform->GetForward();

		Matrix viewRotationMat;
		viewRotationMat._11 = rightVector.x; viewRotationMat._12 = upVector.x; viewRotationMat._13 = forwardVector.x;
		viewRotationMat._21 = rightVector.y; viewRotationMat._22 = upVector.y; viewRotationMat._23 = forwardVector.y;
		viewRotationMat._31 = rightVector.z; viewRotationMat._32 = upVector.z; viewRotationMat._33 = forwardVector.z;

		mViewMat *= viewRotationMat;
	}
	void Camera::CreateProjectionMatrix()
	{
		RECT windowRect;
		GetClientRect(D3DApp::GetInstance().GetHwnd(), &windowRect);

		float width = (windowRect.right - windowRect.left) * mScale;
		float height = (windowRect.bottom - windowRect.top) * mScale;

		mAspectRatio = width / height;
		
		switch (meProjectionMode)
		{
		case jh::eProjectionMode::PERSPECTIVE_MODE:
			mProjectionMat = Matrix::CreatePerspectiveFieldOfViewLH(
				XM_2PI / 6.0f,										// 60 degree
				mAspectRatio,
				mNearPlain,
				mFarPlain
			);
			break;
		case jh::eProjectionMode::ORTHOGRAPHIC_MODE:
			mProjectionMat = Matrix::CreateOrthographicLH(
				width / 100.0f,
				height / 100.0f,
				mNearPlain,
				mFarPlain
			);
			break;
		default:
			assert(false);
			break;
		}

	}

	void Camera::TurnLayerMask(const eLayerType eLayer, const bool bIsEnable)
	{
		mLayerMasks.set(static_cast<UINT>(eLayer), bIsEnable);
	}
}