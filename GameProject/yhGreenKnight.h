#pragma once
#include "yhGameObject.h"


namespace yh
{
	enum class MonsterState
	{
		Idle,
		Move,
		Attack,
		MoveReady,
		Death,
		Falling,
		Ui,
		End,
	};


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

		void Idle();
		void MoveReady();
		void Move();
		void Attack();
		void Death();
		void Falling();
		void Ui();

	private:
		class Animator* anim;
		class Collider* col;
		class Transform* tr;
		MonsterState state;
		Directions direction;

		float moving_time;
	};
}


