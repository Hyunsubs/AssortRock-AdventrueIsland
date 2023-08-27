#pragma once
#include "yhScene.h"



namespace yh
{
	class EndingScene : public Scene
	{
	public:
		EndingScene();
		virtual ~EndingScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:
		class AsciiRender* ascii;
		bool is_played;
	};
}


