#include "yhArrow.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"

namespace yh
{
	Arrow::Arrow() :
		  image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		std::wstring UI_path = UI_PATH;
		image = Resources::Load<Texture>(L"ArrowUI", UI_path + L"Arrow\\arrow.bmp");
		sr = AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(2.5f, 2.5f));
		SetState(GameObject::eState::Pause);
	}
	Arrow::~Arrow()
	{
	}
	void Arrow::Initialize()
	{
	}
	void Arrow::Update()
	{
		GameObject::Update();
	}
	void Arrow::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}