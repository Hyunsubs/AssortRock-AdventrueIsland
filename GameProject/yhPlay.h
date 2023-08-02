#pragma once
#include "CommonInclude.h"
#include "yhSpriteRenderer.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhPlayerTemplate.h"

namespace yh
{
	class Play : public PlayerTemplate
	{
	public:
		Play();
		virtual ~Play();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
	private:
		class Player* player;
	};
}


