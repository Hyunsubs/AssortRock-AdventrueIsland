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
			Right
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

		PlayerState GetState() { return state; }
		void SetState(PlayerState pstate) { state = pstate; }

	private:
		PlayerState state;
		Directions direction;
		class PlayerSword* sword;
		int hp;
		int mp;
	};
}


