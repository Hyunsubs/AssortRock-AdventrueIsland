#pragma once
#include "CommonInclude.h"
#include "yhSpriteRenderer.h"
#include "yhLayer.h"
#include "yhObject.h"

namespace yh
{
	using namespace math;
	class PlayerTemplate : public Scene
	{
	public:
		PlayerTemplate();
		virtual ~PlayerTemplate();

		virtual void Initialize();
		virtual void Update(Vector2 size);
		virtual void Render(HDC hdc);

		Vector2 GetPlayerPos();
		void SetPlayerPos(Vector2 pos);
		void Save(std::string path);
		void Load(std::string path);
		void LoadPosition();
		void SavePosition();

		void SetMapPos(Vector2 input) { map_pos = input; }
		void SetMapScale(Vector2 input) { map_scale = input; }
		class Player* GetPlayer() { return player; }


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
		class Number* rupee_first_digit;
		class Number* rupee_second_digit;
		class Number* rupee_third_digit;
		class Number* arrow_first_digit;
		class Number* arrow_second_digit;
		class Number* bomb_first_digit;
		class Number* bomb_second_digit;

		Vector2 map_scale;
		Vector2 map_pos;

		std::vector<class HpInterface*> hp_container;


		
	};
}