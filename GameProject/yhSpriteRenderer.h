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
		void SetAffectCamera(bool enable) { mbAffectCamera = enable; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }
		void SetTile(int x, int y) { mbTile = true; mTileIndexX = x; mTileIndexY = y; }

	private:
		bool mbAffectCamera;

		bool mbTile;
		int mTileIndexX;
		int mTileIndexY;


		Texture* mTexture;
		Vector2 mScale;
		float mAlpha;
	};
}


