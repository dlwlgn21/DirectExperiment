#include "jhLight.h"
#include "jhTransform.h"
#include "jhLightingManager.h"
#include "jhLayerZValue.h"

using namespace jh::math;

namespace jh
{
	Light::Light(const LightAttribute& lightAttribute)
		: Component(eComponentType::LIGHT)
		, mLightAttirbute(lightAttribute)
		, mpTransform(nullptr)
		, mpFollowingTransform(nullptr)
	{
	}

	void Light::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
	}

	void Light::FixedUpdate()
	{
		if (mpFollowingTransform == nullptr)
		{
			assert(mpTransform != nullptr);
			Vector3 pos = mpTransform->GetPosition();
			Vector3 direction = mpTransform->GetRight();
			mLightAttirbute.Position = Vector4(pos.x, pos.y, pos.z, 1.0f);
			mLightAttirbute.Direction = Vector4(direction.x, direction.y, direction.z, 1.0f);
		}
		else
		{
			Vector3 followingPos = mpFollowingTransform->GetPosition();
			Vector3 pos = Vector3(followingPos.x, followingPos.y, BG_LIGHT_Z_VALUE);
			Vector3 direction = mpFollowingTransform->GetRight();
			mLightAttirbute.Position = Vector4(pos.x, pos.y, pos.z, 1.0f);
			mLightAttirbute.Direction = Vector4(direction.x, direction.y, direction.z, 1.0f);
		}
		LightingManager::GetInstance().PushLightAttribute(mLightAttirbute);

	}

}
