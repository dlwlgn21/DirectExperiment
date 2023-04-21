#include "jhParallaxScript.h"
#include "jhTime.h"
#include "jhInput.h"
#include "jhResourceMaker.h"
#include "jhTransform.h"
#include "jhCameraManager.h"

using namespace jh::math;


static constexpr const float ASPECT_RATIO = 9.24f;
static constexpr const float MAG = 10.0f;
namespace jh
{
	ParallaxScript::ParallaxScript(const float zValue, const float parallaxFactor)
		: Script()
		, mpTransform(nullptr)
		, mStartPos(Vector2::Zero)
		, mTravelVector(Vector2::Zero)
		, mParallaxFactor(parallaxFactor)
		, mOriginZ(zValue)
		, mStartZ(0.0f)
		, mpCameraTransform(CameraManager::GetInstance().GetMainCamera()->GetOwner()->GetTransform())
	{
		assert(mpCameraTransform != nullptr);
	}
	void ParallaxScript::Initialize()
	{
		mpTransform = GetOwner()->GetTransform();
		assert(mpTransform != nullptr);
		Vector3 startPos(mpCameraTransform->GetPosition());
		mStartPos.x = startPos.x;
		mStartPos.y = startPos.y;
		mStartZ = startPos.z;
	}
	void ParallaxScript::Update()
	{
		Vector2 cameraPos(mpCameraTransform->GetPosition());
		mTravelVector = cameraPos - mStartPos;
		mpTransform->SetPosition(Vector3(mTravelVector.x * mParallaxFactor, mpTransform->GetPosition().y, mOriginZ));
	}
	void ParallaxScript::FixedUpdate()
	{
	}
	void ParallaxScript::Render()
	{
	}

}