#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void CheckKeyDown(class Animator* anim);
		void CheckKeyUp(class Animator* anim);
		void CheckKey(class Transform* tr, class Animator* anim);
	private:
	};
}


