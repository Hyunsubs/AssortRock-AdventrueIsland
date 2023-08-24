#pragma once
#include "yhGameObject.h"

namespace yh
{
	class ArrghusShadow : public GameObject
	{
	public:
		ArrghusShadow();
		virtual ~ArrghusShadow();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Transform* tr;
		class Texture* image;
		class SpriteRenderer* sr;
		
		
	};
}


