#include "jhAudioSorceScrpt.h"
#include "jhTransform.h"

using namespace jh::math;

namespace jh
{
	AudioSorceScript::AudioSorceScript(Transform* pFollowingTransform)
		: Script()
		, mpFollowingTransform(pFollowingTransform)
	{
		assert(mpFollowingTransform != nullptr);
	}

	void AudioSorceScript::Update()
	{
		GetOwner()->GetTransform()->SetPosition(mpFollowingTransform->GetPosition());
	}
}