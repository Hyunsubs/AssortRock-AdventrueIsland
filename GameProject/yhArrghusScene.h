#pragma once
#include "yhPlayerTemplate.h"


namespace yh
{

	class ArrghusScene : public PlayerTemplate
	{
	public:
		ArrghusScene();
		virtual ~ArrghusScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class Arrghus* boss;
		class MapChanger* to_ganon;

		Vector2 map_pos;
		Vector2 map_scale;
		Vector2 map_size;
	};
}


