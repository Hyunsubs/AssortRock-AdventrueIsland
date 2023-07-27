#pragma once
#include "yhScene.h"

namespace yh
{
	class House : public Scene
	{
	public:
		House();
		virtual ~House();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:
	};
}


