#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Mana : public GameObject
	{
	public:
		Mana();
		virtual ~Mana();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		int GetMp() { return mp; }
		void SetMp(int number) { mp = number; }

	private:
		int mp;
		class SpriteRenderer* sr;
		class Texture* image;
		class Transform* tr;
	};
}


