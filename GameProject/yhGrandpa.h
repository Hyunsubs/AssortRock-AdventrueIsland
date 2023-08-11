#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Grandpa : public GameObject
	{
	public:
		Grandpa();
		virtual ~Grandpa();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		class Animator* anim;
		class Transform* tr;
		class Collider* col;
		class AsciiRender* ascii;
		int idx;
		std::vector<class AsciiRender*> dialogue;
	};
}