#include "jhCollisionManager.h"
#include "jhSceneManager.h"
#include "jhCollider2D.h"
#include "jhGameObject.h"
#include "jhScene.h"
#include "jhTransform.h"

using namespace jh::math;

namespace jh
{
	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{

	}

	void CollisionManager::FixedUpdate()
	{
		Scene* pCurrScene = SceneManager::GetInstance().GetCurrentScene();
		assert(pCurrScene != nullptr);

		for (UINT row = 0; row < static_cast<UINT>(eLayerType::COUNT); ++row)
		{
			for (UINT col = 0; col < static_cast<UINT>(eLayerType::COUNT); ++col)
			{
				if (mLayerCollisionMatrix[row][col])
				{
					checkLayerCollision(pCurrScene, static_cast<eLayerType>(row), static_cast<eLayerType>(col));
				}
			}
		}
	}
	void CollisionManager::Render()
	{
	}
	void CollisionManager::SetCollisionLayerCheck(const eLayerType eLeftLayer, const eLayerType eRightLayer, const bool bIsEnable)
	{
		UINT row = 0;
		UINT col = 0;
		UINT leftNum = static_cast<UINT>(eLeftLayer);
		UINT rightNum = static_cast<UINT>(eRightLayer);
		if (leftNum <= rightNum)
		{
			row = leftNum;
			col = rightNum;
		}
		else
		{
			row = rightNum;
			col = leftNum;
		}
		mLayerCollisionMatrix[row][col] = bIsEnable;
	}


	void CollisionManager::checkLayerCollision(Scene* pScene, const eLayerType eLeftLayer, const eLayerType eRightLayer)
	{
		auto& leftLayerGameObjects = pScene->GetAllGameObjectsFromSpecifiedLayer(eLeftLayer);
		auto& rightLayerGameObjects = pScene->GetAllGameObjectsFromSpecifiedLayer(eRightLayer);

		for (auto* pLeftObject : leftLayerGameObjects)
		{
			if (pLeftObject->GetState() != GameObject::eGameObjectState::ACTIVE)	{continue;}
			Collider2D* pLeftCollider = static_cast<Collider2D*>(pLeftObject->GetComponentOrNull(eComponentType::COLLIDER));

			if (pLeftCollider == nullptr) {continue;}

			for (auto* pRightObject : rightLayerGameObjects)
			{
				if (pRightObject->GetState() != GameObject::eGameObjectState::ACTIVE) { continue; }
				Collider2D* pRightCollider = static_cast<Collider2D*>(pRightObject->GetComponentOrNull(eComponentType::COLLIDER));
				if (pRightCollider == nullptr) {continue;}
				if (pLeftCollider == pRightCollider) {continue;}
				if (pLeftCollider->GetState() != eColliderState::ACTIVE || pRightCollider->GetState() != eColliderState::ACTIVE) { continue; }
				checkValidColliderCollision(pLeftCollider, pRightCollider);
			}

		}
	}

	void CollisionManager::checkValidColliderCollision(Collider2D* pLeftCollider, Collider2D* pRightCollider)
	{
		ColliderID colliderID;
		colliderID.Left = static_cast<UINT32>(pLeftCollider->GetColliderID());
		colliderID.Right = static_cast<UINT32>(pRightCollider->GetColliderID());

		// ���� �浹 ������ �˻�.

		auto findResIter = mCollisionMap.find(colliderID.Id);
		// ColliderID�� �˻��ؼ� ���ٸ� �浹���� ���� ��.
		// �浹������ ��������.
		if (findResIter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.Id, false));
			findResIter = mCollisionMap.find(colliderID.Id);
		}

		// ������ �浹���� �������� �浹üũ ����.
		if (isIntersect(pLeftCollider, pRightCollider))
		{

			// �浹 ������ ���� ���� Enter
			if (findResIter->second == false)
			{
				if (pLeftCollider->GetIsUsePhysics())
				{
					pLeftCollider->OnCollisionEnter(pRightCollider);
				}
				else
				{
					pLeftCollider->OnTriggerEnter(pRightCollider);
				}

				if (pRightCollider->GetIsUsePhysics())
				{
					pRightCollider->OnCollisionEnter(pLeftCollider);
				}
				else
				{
					pRightCollider->OnTriggerEnter(pLeftCollider);
				}
				findResIter->second = true;
			}
			// �̹� �浹 ���� ���� Stay
			else
			{
				if (pLeftCollider->GetIsUsePhysics())
				{
					pLeftCollider->OnCollisionStay(pRightCollider);
				}
				else
				{
					pLeftCollider->OnTriggerStay(pRightCollider);
				}

				if (pRightCollider->GetIsUsePhysics())
				{
					pRightCollider->OnCollisionStay(pLeftCollider);
				}
				else
				{
					pRightCollider->OnTriggerStay(pLeftCollider);
				}
			}
		}
		else // �ƿ� �浹���� ���� ����
		{
			// �� ���� ���� ���� Exit
			if (findResIter->second == true)
			{
				if (pLeftCollider->GetIsUsePhysics())
				{
					pLeftCollider->OnCollisionExit(pRightCollider);
				}
				else
				{
					pLeftCollider->OnTriggerExit(pRightCollider);
				}

				if (pRightCollider->GetIsUsePhysics())
				{
					pRightCollider->OnCollisionExit(pLeftCollider);
				}
				else
				{
					pRightCollider->OnTriggerExit(pLeftCollider);
				}

				// �����������ϱ� �浹���� �ƴ�. �������� ���� ������Ʈ.
				findResIter->second = false;
			}
		}
	}

	bool CollisionManager::isIntersect(Collider2D* pLeftCollider, Collider2D* pRightCollider)
	{
		assert(pLeftCollider != nullptr && pRightCollider != nullptr);
		static const int RECT_VECTEX_COUNT = 4;
		Transform* pLeftTransform = pLeftCollider->GetOwner()->GetTransform();
		Transform* pRightTransform = pRightCollider->GetOwner()->GetTransform();

		const Matrix& leftWorldMat = pLeftTransform->GetWorldMatrix();
		const Matrix& rightWorldMat = pRightTransform->GetWorldMatrix();

		Vector3 arrLocalPos[RECT_VECTEX_COUNT] =
		{
			Vector3{-0.5f, 0.5f, 0.0f},
			Vector3{0.5f, 0.5f, 0.0f},
			Vector3{0.5f, -0.5f, 0.0f},
			Vector3{-0.5f, -0.5f, 0.0f}
		};

		Vector3 Axis[RECT_VECTEX_COUNT] = {};

		Vector3 leftScale = Vector3(pLeftCollider->GetSize().x, pLeftCollider->GetSize().y, 1.0f);

		Matrix finalLeftMat = Matrix::CreateScale(leftScale);
		finalLeftMat *= leftWorldMat;

		Vector3 rightScale = Vector3(pRightCollider->GetSize().x, pRightCollider->GetSize().y, 1.0f);
		Matrix finalRightMat = Matrix::CreateScale(rightScale);
		finalRightMat *= rightWorldMat;

		Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeftMat);
		Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeftMat);
		Axis[2] = Vector3::Transform(arrLocalPos[1], finalRightMat);
		Axis[3] = Vector3::Transform(arrLocalPos[3], finalRightMat);

		Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeftMat);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeftMat);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRightMat);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRightMat);

		
		for (UINT i = 0; i < RECT_VECTEX_COUNT; i++)
		{
			Axis[i].z = 0.0f;
		}

		Vector3 vc = pLeftTransform->GetPosition() - pRightTransform->GetPosition();
		vc.z = 0.0f;

		Vector3 centerDir = vc;

		for (UINT i = 0; i < RECT_VECTEX_COUNT; i++)
		{
			Vector3 vA = Axis[i];
			//vA.Normalize();

			float projectionDistance = 0.0f;
			for (UINT j = 0; j < RECT_VECTEX_COUNT; j++)
			{
				projectionDistance += fabsf(Axis[j].Dot(vA) * 0.5f);
			}

			if (projectionDistance < fabsf(centerDir.Dot(vA)))
			{
				return false;
			}
		}

		return true;
	}
}