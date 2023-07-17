#pragma once
#include "yhScene.h"

namespace yh
{
	class TitleAnimation : public Scene
	{
	public:
		TitleAnimation();
		virtual ~TitleAnimation();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		float GetChangeTime() { return m_change_time; }
		void SetChangeTime(float time) { m_change_time = time; }
		
	private:
		float m_change_time = 0.0f;
		
	};
}


