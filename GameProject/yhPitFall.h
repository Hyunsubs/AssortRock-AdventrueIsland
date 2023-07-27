#pragma once
#include "yhGameObject.h"


namespace yh
{
	class PitFall : public GameObject
	{
	public:
		PitFall();
		~PitFall();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	};
}


