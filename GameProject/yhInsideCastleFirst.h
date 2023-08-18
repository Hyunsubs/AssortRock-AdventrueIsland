#pragma once
#include "yhPlayerTemplate.h"


namespace yh
{

	class InsideCastleFirst : public PlayerTemplate
	{
	public:
		InsideCastleFirst();
		virtual ~InsideCastleFirst();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Vector2 map_pos;
		Vector2 map_scale;
		Vector2 map_size;

		std::vector<class Step*> steps;
		std::vector<class Stair*> stairs;


		class MapChanger* to_castle_garden;
		class MapChanger* to_castle_second;
		class MapChanger* to_castle_third;

		class GreenKnight* gn_first;
		class GreenKnight* gn_second;
	};
}
