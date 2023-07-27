#pragma once
#include "yhGameObject.h"

namespace yh
{
	class PlayerSword : public GameObject
	{
	public:
		enum class SwordState
		{
			Idle,
			Move,
			Attack,
			Death,
			Map,
			Falling,
			Carrying,
			Ui,
			End,
		};

		enum class Directions
		{
			Forward,
			Backward,
			Left,
			Right,
			None,
		};



		PlayerSword();
		virtual ~PlayerSword();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();
		void Move();
		void Attack();
		void Death();
		void Map();
		void Falling();
		void Ui();

	private:
		SwordState state;
		Directions direction;
		class Animator* sword_anim;
		class Collider* col;
	};
}
