#define _CRT_SECURE_NO_WARNINGS
#include "jhMonsterUIMesh.h"
#include "jhGraphicDeviceDX11.h"
#include "jhMonsterUIManager.h"
#include "jhGameObject.h"

namespace jh
{
	MonsterUIMesh::MonsterUIMesh()
		: Mesh()
	{

	}
	void MonsterUIMesh::Render()
	{
		MonsterUIManager::GetInstance().SetPipeline();
		graphics::GraphicDeviceDX11::GetInstance().GetDeivceContext()->DrawIndexed(mIndexCount, 0, 0);
	}
}