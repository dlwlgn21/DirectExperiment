#include "jhComponent.h"


namespace jh
{
	Component::Component(eComponentType eType)
		: mpOwner(nullptr)
		, meType(eType)
	{
	}

	Component::~Component()
	{
	}

	void Component::Initialize()
	{
	}

	void Component::Update()
	{
	}

	void Component::FixedUpdate()
	{
	}

	void Component::Render()
	{
	}

}
