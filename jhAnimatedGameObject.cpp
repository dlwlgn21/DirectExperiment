#include "jhAnimatedGameObject.h"


namespace jh
{
	AnimatedGameObject::AnimatedGameObject()
		: GameObject(eLayerType::EFFECT)
	{

	}
	void AnimatedGameObject::Initialize()
	{
		GameObject::Initialize();
	}
	void AnimatedGameObject::Update()
	{
		GameObject::Update();
	}
	void AnimatedGameObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void AnimatedGameObject::Render()
	{
		GameObject::Render();
	}

	void AnimatedGameObject::setAnimator()
	{
	}

	void AnimatedGameObject::setRenderer()
	{
	}

	void AnimatedGameObject::setScript()
	{
	}

}