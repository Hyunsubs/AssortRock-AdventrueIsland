#pragma once
#include "yhGameObject.h"

namespace yh
{
	using namespace math;


	class MonsterTemplate : public GameObject
	{
	public:
		MonsterTemplate();
		virtual ~MonsterTemplate();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void Idle();
		virtual void Move();
		virtual void MoveReady();
		virtual void Attack();
		virtual void Death();
		virtual void KnockBack();
		virtual void Falling();
		virtual void Ui();
		virtual void Chasing();

		virtual void SetState(MonsterState input) { state = input; }

		virtual void CheckChasing();
		virtual void CheckPixel(class Texture* pixel_texture, Vector2 map_size);

		void SetClutch(bool input) { got_clutch = input; }

		int GetHp() { return hp; }
		void SetHp(int input) { hp = input; }

		MonsterState GetMonsterState() { return state; }


		class Texture* PixelTexture;
		Vector2 map_size;

		class Animator* anim;
		class Collider* col;
		class Transform* tr;

	private:

		MonsterState state;
		Directions direction;

		//체력, 벽 체크 변수
		int hp;
		bool is_Wall;

		bool got_clutch;
		float clutch_time;
		
		//몬스터 공격 맞았을때 밀려나는 시간
		float knock_back_time;
	};
}


