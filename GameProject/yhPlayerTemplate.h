#pragma once
#include "CommonInclude.h"
#include "yhSpriteRenderer.h"
#include "yhLayer.h"
#include "yhObject.h"


namespace yh
{
	class PlayerTemplate : public Scene
	{
	public:
		PlayerTemplate();
		virtual ~PlayerTemplate();

		virtual void Initialize();
		virtual void Update(Vector2 pos);
		virtual void Render(HDC hdc);
	private:
		class PlayerSword* sword;
		class Player* player;
		class ManaPoint* manapoints;
		class Mana* mana;
		class LifeUI* life;
		class Arrow* arrow;
		class Bomb* bomb;
		class RupeeUI* rupee_ui;
		class CurItem* cur_item;
		std::vector<class HpInterface*> hp_container;
	};
}