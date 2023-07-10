#pragma once
#include "yhScene.h"

namespace yh
{
	class Ending : public Scene
	{
	public:
		Ending();
		virtual ~Ending();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	};
}


