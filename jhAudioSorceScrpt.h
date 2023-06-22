#pragma once
#include "jhScript.h"

namespace jh
{
	class Transform;
	class AudioSorceScript final : public Script
	{
	public:
		AudioSorceScript(Transform* pFollowingTransform);
		virtual ~AudioSorceScript() = default;

		void Update() override;

	private:
		Transform* mpFollowingTransform;
	};
}