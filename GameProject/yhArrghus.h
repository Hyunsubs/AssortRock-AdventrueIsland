#pragma once
#include "yhMonsterTemplate.h"


namespace yh
{
	enum class Phase
	{
		First,
		Second
	};
	
	enum class FirstPhase
	{
		Idle,
		Moving,
		Attack,
		None,
	};

	enum class SecondPhase
	{
		Moving,
		Jumping,
		Smashing,
		None,
	};


	class Arrghus : public MonsterTemplate
	{
	public:
		Arrghus();
		virtual ~Arrghus();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);


		void IdleFirst();
		void MovingFirst();
		void AttackFirst();
		
		void MovingSecond();
		void JumpingSecond();
		void SmashingSecond();

		void SetPlayerPos(Vector2 input) { player_pos = input; }

	private:
		class Animator* anim;
		class Transform* tr;
		class Collider* col;

		vector<class ArrghusPiece*> pieces;

		Phase cur_phase;
		FirstPhase first_phase;
		SecondPhase second_phase;
		
		float attack_time;
		float moving_time;
		float idle_time;

		Vector2 piece_pos_arr[15];

		Vector2 player_pos;

		int moving_count;
		float degree;

	};
}


