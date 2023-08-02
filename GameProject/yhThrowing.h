#pragma once
#include "yhGameObject.h"


namespace yh
{
	using namespace math;
	class Throwing : public GameObject
	{
	public:
		Throwing();
		~Throwing();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Collider* col;
		class SpriteRenderer* sr;
		class Transform* tr;
	};
}

