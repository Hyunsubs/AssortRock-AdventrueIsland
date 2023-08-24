#pragma once
#include "yhGameObject.h"

namespace yh
{
	


	class GanonTrident : public GameObject
	{
	public:
		GanonTrident();
		virtual ~GanonTrident();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayerPos(Vector2 input) { Player_Pos = input; }
	private:
		class Transform* tr;
		class Animator* anim;
		class Collider* col;
		
		Vector2 Player_Pos;
		Directions direct;
		float exist_time;

	};
}


