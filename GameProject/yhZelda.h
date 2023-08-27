#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Zelda : public GameObject
	{
	public:
		Zelda();
		virtual ~Zelda();

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
		class Sound* end_sound;

		bool end_played;

		int idx;
		std::vector<class AsciiRender*> dialogue;
	};
}