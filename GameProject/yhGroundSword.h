#pragma once
#include "yhGameObject.h"

namespace yh
{
	class GroundSword : public GameObject
	{
	public:
		GroundSword();
		virtual ~GroundSword();


		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
	
		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Texture* image;
		class SpriteRenderer* sr;
		class Transform* tr;
		class AsciiRender* ar;
		class Collider* col;


	};
}


