#pragma once
#include "yhGameObject.h"

#define FLYING_TIME 1.0f


namespace yh
{
	class Boomerang : public GameObject
	{
	public:
		enum class BoomerangState
		{
			Idle,
			Move,
			MoveBack,
			Death,
			End,
		};


		Boomerang();
		virtual ~Boomerang();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();
		void Move();
		void MoveBack(Vector2 player_pos);
		void Death();

		void SetDirection(Directions direct) { direction = direct; }
		
		void SetBoomerangState(BoomerangState input) { state = input; }
		BoomerangState GetBoomerangState() { return state; }

		void SetPlayerPos(Vector2 pos) { player_pos = pos; }

	private:
		BoomerangState state;
		Directions direction;
		Vector2 player_pos;
		float flying_time;

		class Animator* boomerang_anim;
		class Collider* col;
		class Transform* tr;
	};
}


