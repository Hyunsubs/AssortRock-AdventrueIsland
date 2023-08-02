#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Player : public GameObject
	{
	public:
		enum class PlayerState
		{
			Idle,
			Move,
			Attack,
			Charge,
			Death,
			Map,
			Hit,
			Falling,
			Carrying,
			Throwing,
			Ui,
			End,
		};




		Player();
		virtual ~Player();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void Idle();
		void Move();
		void Attack();
		void Death();
		void Map();
		void Falling();
		void Ui();
		void Carrying();
		void Throwing();
		void Charge();
		void Hit();

		PlayerState GetState() { return state; }
		void SetState(PlayerState pstate) { state = pstate; }

		Directions GetDirection() { return direction; }
		void SetDirection(Directions direct) { direction = direct; }

		int GetMp() { return mp; }
		int GetHp() { return hp; }
		int GetMaxHp() { return max_hp; }

		void SetMp(int num) { mp = num; }
		void SetHp(int num) { hp = num; }
		void SetMaxHp(int num) { max_hp = num; }


		bool GetThrowing() { return is_Throwing; }
		void SetThrowing(bool input) { is_Throwing = input; }

		bool GetIsWall() { return is_Wall; }
		void SetIsWall(bool input) { is_Wall = input; }

	private:
		PlayerState state;
		Directions direction;
		std::vector<class HpInterface*> hp_container;
		bool is_Throwing;
		bool is_Wall;
		class PlayerSword* sword;
		class PlayerShield* shield;
		class Mana* mana;
		class Sound* AttackSound;
		class Animator* at;
		class Sound* Alert;
		bool is_dead;
		int max_hp;
		int hp;
		int mp;
		int rupee;
		int bomb;
		int arrow;
		int charge_time;
	};
}


