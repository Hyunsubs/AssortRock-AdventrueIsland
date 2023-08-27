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

		bool GetSword() { return get_sword; }
		void Set_GetSword(bool input) { get_sword = input; }


		SwordState GetSwordState() { return state; }

	private:
		SwordState state;
		Directions direction;
		bool is_Throwing;
		bool get_sword;
		class Animator* sword_anim;
		class Collider* col;
		class Sound* hit_sound;
	};
}
