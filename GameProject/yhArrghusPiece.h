#pragma once
#include "yhMonsterTemplate.h"

namespace yh
{
	enum class PieceState
	{
		Idle,
		Move,
		Attack,
		Grapped,
		Dead
	};

	enum class Intensity
	{
		Slow,
		Middle,
		Fast,
		Jiral
	};

	class ArrghusPiece : public MonsterTemplate
	{
	public:
		ArrghusPiece();
		virtual ~ArrghusPiece();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();
		void Move();
		void Attack();
		void Grapped();
		void Dead();

	private:
		PieceState state;
		bool is_seperated;

		class Animator* anim;
		class Transform* tr;
		class Collider* col;

		Vector2 main_pos;
		Vector2 attack_pos;

		Directions direct;

		float idle_time;
		float move_time;
		float attack_time;
		float degree;

		int move_count;


	};
}


