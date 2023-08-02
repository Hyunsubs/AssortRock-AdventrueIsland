#pragma once
#include "yhPlayerTemplate.h"


namespace yh
{
	class House : public PlayerTemplate
	{
	public:
		House();
		virtual ~House();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:
		class Player* player;
	};
}


