#pragma once
#include "yhGameObject.h"

namespace yh
{
	class BackGroundAnimation : public GameObject
	{
	public:
		BackGroundAnimation();
		virtual ~BackGroundAnimation();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	};
}



