#pragma once
#include "yhGameObject.h"

namespace yh
{
	class HeartContainer : public GameObject
	{
	public:
		HeartContainer();
		virtual ~HeartContainer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Transform* tr;
		class SpriteRenderer* sr;
		class Texture* image;
		class Collider* col;
		class AsciiRender* ar;
		class Sound* get_sound;

		bool sound_played;

	};
}


