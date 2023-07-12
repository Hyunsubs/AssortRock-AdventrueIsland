#pragma once
#include "yhScene.h"

namespace yh
{
	class NameInput : public Scene
	{
	public:
		NameInput();
		virtual ~NameInput();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	};
}


