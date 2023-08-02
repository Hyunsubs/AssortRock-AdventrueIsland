#pragma once
#include "yhGameObject.h"


namespace yh
{
	class LifeUI : public GameObject
	{
	public:
		LifeUI();
		virtual ~LifeUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;



	private:
		class SpriteRenderer* sr;
		class Texture* image;
		class Transform* tr;

	};
}

