#include "jhLight.h"
#include "jhTransform.h"
#include "jhLightingManager.h"

using namespace jh::math;

namespace jh
{
	Light::Light(const LightAttribute& lightAttribute)
		: Component(eComponentType::LIGHT)
		, mLightAttirbute(lightAttribute)
		, mpTransform(nullptr)
	{
	}

	void Light::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
	}
	void Light::Update()
	{
	}
	void Light::FixedUpdate()
	{
		assert(mpTransform != nullptr);
		Vector3 pos = mpTransform->GetPosition();
		Vector3 direction = mpTransform->GetRight();
		mLightAttirbute.Position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mLightAttirbute.Direction = Vector4(direction.x, direction.y, direction.z, 1.0f);

		LightingManager::GetInstance().PushLightAttribute(mLightAttirbute);
	}
	void Light::Render()
	{
	}
}
