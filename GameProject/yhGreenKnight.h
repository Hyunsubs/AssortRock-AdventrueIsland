#pragma once
#include "yhMonsterTemplate.h"


namespace yh
{
	using namespace math;

	class GreenKnight : public GameObject
	{
	public:
		GreenKnight();
		~GreenKnight();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void Idle();
		virtual void Move();
		virtual void Attack();
		virtual void Death();
		virtual void Falling();
		virtual void Ui();
		virtual void Chasing();


		void SetChasing(bool input) { is_chasing = input; }
		void SetPlayerPos(Vector2 pos) { player_pos = pos; }

		void SetState(MonsterState input) { state = input; }
		MonsterState GetMonsterState() { return state; }

		int GetHp() { return hp; }
		void SetHp(int input) { hp = input; }

		void CheckChasing();
		virtual void CheckPixel(class Texture* pixel_texture, Vector2 map_size);

		class Texture* PixelTexture;
		Vector2 map_size;


	private:
		class Animator* anim;
		class Collider* col;
		class Transform* tr;
		MonsterState state;
		Directions direction;

		Vector2 player_pos;
		float moving_time;
		bool is_Wall;
		bool is_chasing;
	
		int hp;
	};
}


