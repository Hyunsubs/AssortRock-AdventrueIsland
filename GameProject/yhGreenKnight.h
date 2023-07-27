#pragma once
#include "yhGameObject.h"


namespace yh
{
	class GreenKnight : public GameObject
	{
	public:
		GreenKnight();
		~GreenKnight();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);
	};
}


