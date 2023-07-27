#pragma once
#include "CommonInclude.h"
#include "yhSpriteRenderer.h"
#include "yhLayer.h"
#include "yhObject.h"

namespace yh
{
	class Play : public Scene
	{
	public:
		Play();
		virtual ~Play();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
	private:
		class PlayerSword* sword;
	};
}


