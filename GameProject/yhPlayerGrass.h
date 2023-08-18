#pragma once
#include "yhGameObject.h"

namespace yh
{

	class PlayerGrass : public GameObject
	{
	public:
		PlayerGrass();
		virtual ~PlayerGrass() override;



		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


	private:
		class Transform* tr;
		class Texture* image;
		class SpriteRenderer* sr;

	};
}


