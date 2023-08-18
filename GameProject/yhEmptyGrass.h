#pragma once
#include "yhGameObject.h"


namespace yh
{
	class EmptyGrass : public GameObject
	{
	public:
		EmptyGrass();
		virtual ~EmptyGrass();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Texture* image;
		class SpriteRenderer* sr;
		class Transform* tr;
		



	};
}


