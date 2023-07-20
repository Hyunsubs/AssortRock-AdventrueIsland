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


	}

	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}

