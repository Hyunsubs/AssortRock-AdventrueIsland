#pragma once
#include "yhPlayerTemplate.h"


namespace yh
{

	class GanonScene : public PlayerTemplate
	{
	public:
		GanonScene();
		virtual ~GanonScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Vector2 map_pos;
		Vector2 map_scale;
		Vector2 map_size;

		class Ganon* boss;
		class Zelda* zelda;
		bool first_talking;
		bool second_talking;

		class SpriteRenderer* bgsr;
		class Sound* end_sound;

		float cur_alpha;
	};
}
