#pragma once
#include "yhGameObject.h"

namespace yh
{
	enum class BatsState
	{
		Moving,
		Following,
		Dead,
		None,
	};

	class GanonFireBats : public GameObject
	{
	public:
		GanonFireBats();
		virtual ~GanonFireBats();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayerPos(Vector2 input) { Player_Pos = input; }
		void SetBossPos(Vector2 input) { boss_pos = Vector2(input.x - 30.0f, input.y - 30.0f); }

		void Moving(Vector2 pos);
		void Following();

		int CheckPlayerPos();
	private:
		Vector2 Player_Pos;
		Vector2 boss_pos;
		float degree;
		float following_time;

		class Animator* anim;
		class Transform* tr;
		class Collider* col;

		BatsState state;
		int type;
	};

}

