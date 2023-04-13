#include "jhEditor.h"
#include "jhResourcesManager.h"
#include "jhResourceMaker.h"
#include "jhMesh.h"
#include "jhMaterial.h"
#include "jhTransform.h"
#include "jhDebugObject.h"
#include "jhMeshRenderer.h"
#include "jhCameraManager.h"
#include "jhCamera.h"

namespace jh
{
	void Editor::Initalize()
	{
		mDebugObjects.reserve(static_cast<UINT>(eColliderShapeType::COUNT));
		mDebugObjects.resize(static_cast<UINT>(eColliderShapeType::COUNT));
		Mesh* pMesh = ResourcesManager::Find<Mesh>(ResourceMaker::DEBUG_RECT_MESH_KEY);
		assert(pMesh != nullptr);
		Material* pMaterial = ResourcesManager::Find<Material>(ResourceMaker::DEBUG_MATERIAL_KEY);
		assert(pMaterial != nullptr);
		mDebugObjects[static_cast<UINT>(eColliderShapeType::RECT)] = new DebugObject();
		MeshRenderer* pMeshRenderer = new MeshRenderer(pMesh, pMaterial);
		mDebugObjects[static_cast<UINT>(eColliderShapeType::RECT)]->AddComponent(pMeshRenderer);
		pMeshRenderer->Initialize();
	}
	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void Editor::Update()
	{
	}
	void Editor::FixedUpdate()
	{
	}
	void Editor::Render()
	{
		std::vector<DebugMesh>& debugMeshs = ResourceMaker::GetInstance().GetDebugMeshs();
		
		for (const auto& debugMesh : debugMeshs)
		{
			DebugRender(debugMesh);
		}

		debugMeshs.clear();
	}
	void Editor::Release()
	{
		for (auto* pDebugObject : mDebugObjects)
		{
			if (pDebugObject != nullptr)
			{
				delete pDebugObject;
			}
		}
	}
	void Editor::DebugRender(const DebugMesh& mesh)
	{
		DebugObject* pDebugObject = mDebugObjects[static_cast<UINT>(mesh.EColiiderShapeType)];
		assert(pDebugObject != nullptr);

		Transform* pTransform = pDebugObject->GetTransform();
		assert(pTransform != nullptr);
		pTransform->SetPosition(mesh.Position);
		pTransform->SetRotation(mesh.Rotation);

		if (mesh.EColiiderShapeType == eColliderShapeType::RECT)
		{
			pTransform->SetScale(mesh.Scale);
		}
		else
		{
			assert(false);
		}

		Camera* pCamera = CameraManager::GetInstance().GetMainCamera();
		
		pTransform->FixedUpdate();

		Camera::SetGpuViewMatrix(pCamera->GetViewMatrix());
		Camera::SetGpuProjectionMatrix(pCamera->GetProjectionMatrix());

		pDebugObject->Render();
	}
}