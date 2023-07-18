#include "yhFadeInBackground.h"
#include "yhSpriteRenderer.h"
#include "yhTime.h"

namespace yh
{

	FadeInBackground::FadeInBackground()
	{

	}
	FadeInBackground::~FadeInBackground()
	{
	}
	void FadeInBackground::Initialize()
	{
	}

	void FadeInBackground::Update()
	{
		GameObject::Update();
		SpriteRenderer* sr = GetComponent<SpriteRenderer>();

		float alpha = sr->GetAlpha();
		alpha -= 0.1f * Time::DeltaTime();
		sr->SetAlpha(alpha);
		

	}
	void FadeInBackground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}