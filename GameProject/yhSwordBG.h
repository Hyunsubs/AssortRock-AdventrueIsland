#pragma once
#include "yhGameObject.h"

namespace yh
{
	class SwordBG : public GameObject
	{
	public:
		SwordBG();
		virtual ~SwordBG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	};
}

