#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhGameObject.h"


namespace yh
{
	
	yh::SpriteRenderer::SpriteRenderer()
		:Component(eComponentType::SpriteRenderer)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Ellipse(hdc, 100 + pos.x, 100 + pos.y,
			200 + pos.x, 200 + pos.y);
	}

}
