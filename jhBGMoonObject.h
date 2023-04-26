#include "jhAnimatedGameObject.h"


namespace jh
{
	class BGMoonObject : public AnimatedGameObject
	{
	public:
		BGMoonObject();
		virtual ~BGMoonObject() = default;

	protected:
		void setAnimator() override;
		void setRenderer() override;
		void setScript() override;
	};
}

