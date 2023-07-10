#pragma once
#include "yhScene.h"



namespace yh
{
	class Title : public Scene
	{
	public:
		Title();
		virtual ~Title();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:
	};
}


