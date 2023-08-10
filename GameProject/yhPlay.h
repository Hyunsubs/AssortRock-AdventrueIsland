#pragma once
#include "CommonInclude.h"
#include "yhSpriteRenderer.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhPlayerTemplate.h"

namespace yh
{
	using namespace math;
	class Play : public PlayerTemplate
	{
	public:
		Play();
		virtual ~Play();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	

	private:
		class GreenKnight* knight;
		class MapChanger* castle_to_house;
		class MapChanger* inside_castle;
		class MapChanger* inside_castle2;

		Vector2 map_pos;
		Vector2 map_scale;
		Vector2 map_size;
	};
}


