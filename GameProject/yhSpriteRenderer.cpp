#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhGameObject.h"
#include "yhCamera.h"

namespace yh
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mScale(Vector2::One)
		, mbAffectCamera(true)
		, mTexture(nullptr)
		, mAlpha(1.0f)
	{
	}
	SpriteRenderer::~SpriteRenderer()
	{
	}
	void SpriteRenderer::Initialize()
	{
	}
	void SpriteRenderer::Update()
	{
	}
	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		GameObject* gameObj = GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		mTexture->Render(hdc
			, tr->GetPosition()
			, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, Vector2(0.0f, 0.0f)
			, Vector2(mTexture->GetWidth(), mTexture->GetHeight())
			, Vector2::Zero
			, mScale
			, mAlpha);
		
	}
}
