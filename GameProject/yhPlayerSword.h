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

		void SetThrowing(bool input) { is_Throwing = input; }
		void SetSwordState(SwordState input) { state = input; }

		SwordState GetSwordState() { return state; }

	private:
		SwordState state;
		Directions direction;
		bool is_Throwing;
		class Animator* sword_anim;
		class Collider* col;
	};
}
