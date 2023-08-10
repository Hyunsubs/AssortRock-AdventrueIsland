#pragma once
#include "yhPlayerTemplate.h"


namespace yh
{

	class NearHouseScene : public PlayerTemplate
	{
	public:
		NearHouseScene();
		virtual ~NearHouseScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Vector2 map_pos;
		Vector2 map_scale;
		Vector2 map_size;

		class MapChanger* house_changer;
		class MapChanger* sword_forest;

	};
}

