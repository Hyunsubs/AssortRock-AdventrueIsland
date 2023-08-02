#pragma once
#include "yhGameObject.h"


namespace yh
{
	class RupeeUI : public GameObject
	{
	public:
		RupeeUI();
		virtual ~RupeeUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;



	private:
		class SpriteRenderer* sr;
		class Texture* image;
		class Transform* tr;

	};
}