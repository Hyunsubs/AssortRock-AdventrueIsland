#pragma once
#include "yhMonsterTemplate.h"

#define PIECE_AMOUNT 11

namespace yh
{
	enum class Phase
	{
		First,
		Second
	};
	
	enum class ArrghusFirstPhase
	{
		Idle,
		Moving,
		Attack,
		AttackBack,
		None,
	};

	enum class ArrghusSecondPhase
	{
		Moving,
		Jumping,
		Smashing,
		Dead,
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
		void AttackBackFirst();

		void MovingSecond();
		void JumpingSecond();
		void SmashingSecond(Vector2 attack_pos);
		void Dead();

		virtual void CheckPixel(Texture* pixel_texture, Vector2 map_size);

		Phase GetCurPhase() { return cur_phase; }

		void SetPlayerPos(Vector2 input) { player_pos = input; }

	private:
		class Animator* anim;
		class Transform* tr;
		class Collider* col;

		vector<class ArrghusPiece*> pieces;

		Phase cur_phase;
		ArrghusFirstPhase first_phase;
		ArrghusSecondPhase second_phase;
		
		float attack_time;
		float moving_time;
		float idle_time;

		Vector2 piece_pos_arr[15];

		//플레이어 추적용 위치
		Vector2 player_pos;



		int moving_count;
		float degree;
		float spin_power;
		
		Directions direct;

		bool is_changed;

		//2페이즈
		float second_moving_time;
		float second_smashing_time;
		float second_jumping_time;

		//2페이즈 찍기 패턴 플레이어 공격할 위치
		Vector2 attack_pos;
		//2페이즈 점프 전 보스 위치
		Vector2 jump_pos;
		//2페이즈 그림자
		class ArrghusShadow* arrghus_shadow;

	};
}


