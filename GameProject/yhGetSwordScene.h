#pragma once
#include "yhPlayerTemplate.h"

namespace yh
{
	class GetSwordScene : public PlayerTemplate
	{
	public:
		GetSwordScene();
		virtual ~GetSwordScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);



	private:
		class MapChanger* to_near_house;




		Vector2 map_pos;
		Vector2 map_scale;
		Vector2 map_size;
	};
}


