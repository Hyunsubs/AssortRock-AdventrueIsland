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


		void Idle();
		void Move();
		void Attack();
		void Death();
		void Map();
		void Falling();
		void Ui();

	private:
		PlayerState state;
		Directions direction;
	};
}


