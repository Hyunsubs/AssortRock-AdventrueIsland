#pragma once
#include "yhScene.h"

namespace yh
{
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		virtual ~ToolScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		
	private:

	};
}


