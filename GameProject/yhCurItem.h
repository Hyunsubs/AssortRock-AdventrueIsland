#pragma once
#include "yhGameObject.h"


namespace yh
{
	class CurItem : public GameObject
	{
	public:
		CurItem();
		virtual ~CurItem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;



	private:
		class SpriteRenderer* sr;
		class Texture* image;
		class Transform* tr;

	};
}
