#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhGameObject.h"


namespace yh
{
	
	yh::SpriteRenderer::SpriteRenderer()
		:Component(eComponentType::SpriteRenderer)
		, mScale(Vector2::One)
		, mTexture(nullptr)
	{
	}

	yh::SpriteRenderer::~SpriteRenderer()
	{
	}

	void yh::SpriteRenderer::Initialize()
	{
	}

	void yh::SpriteRenderer::Update()
	{
	}

	void yh::SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (mTexture->GetType() == eTextureType::Bmp)
		{
			TransparentBlt(hdc, (int)pos.x, (int)pos.y
				, mTexture->GetWidth() * mScale.x, mTexture->GetHeight() * mScale.y
				, mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}

		else if (mTexture->GetType() == eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage(), (int)pos.x, (int)pos.y,
				(int)(mTexture->GetWidth() * mScale.x),
				(int)(mTexture->GetHeight() * mScale.y));
		}

		
	}

}
