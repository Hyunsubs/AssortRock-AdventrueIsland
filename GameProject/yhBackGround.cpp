#include "yhBackGround.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhSpriteRenderer.h"


namespace yh
{
	BackGround::BackGround()
	{
	}

	BackGround::~BackGround()
	{
	}

	void BackGround::Initialize()
	{
	}

	void BackGround::Update()
	{
		GameObject::Update();

		/*SpriteRenderer* sr = GetComponent<SpriteRenderer>();

		float alpha = sr->GetAlpha();
		alpha -= 0.2f * Time::DeltaTime();
		sr->SetAlpha(alpha);*/

	}

	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}

