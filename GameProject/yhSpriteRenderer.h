#pragma once
#include "yhComponent.h"
#include "yhTexture.h"

namespace yh
{
	using namespace math;
	class SpriteRenderer : public Component
	{
		
	public:
		
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetImage(Texture* image) { mTexture = image; }
		void SetScale(Vector2 scale) { mScale = scale; }

	private:
		Texture* mTexture;
		Vector2 mScale;
	};
}


