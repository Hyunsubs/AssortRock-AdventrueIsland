#pragma once
#include "yhGameObject.h"

namespace yh
{
	class ArrowProjectile : public GameObject
	{
	public:
		ArrowProjectile();
		virtual ~ArrowProjectile() override;



		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void SetDirection(Directions input) { direct = input; }



	private:
		float flying_time;
		Directions direct;

		class Transform* tr;
		class Texture* image;
		class Collider* col;
		class SpriteRenderer* sr;
	};
}


