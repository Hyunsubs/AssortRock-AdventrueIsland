#pragma once
#include "yhGameObject.h"


namespace yh
{
	using namespace math;
	class Wall : public GameObject
	{
	public:
		Wall();
		~Wall();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetWallSize(Vector2 size);

	private:
		class Collider* col;
	};
}

