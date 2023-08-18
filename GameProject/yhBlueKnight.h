#pragma once
#include "yhMonsterTemplate.h"


namespace yh
{

	class BlueKnight : public MonsterTemplate
	{
	public:
		BlueKnight();
		virtual ~BlueKnight();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);



		void Idle();
		void Move();
		void Attack();
		void Death();
		void Freeze();


	private:

		Directions direct;

		MonsterState state;
		float freeze_time;
		float move_time;

	};
}


