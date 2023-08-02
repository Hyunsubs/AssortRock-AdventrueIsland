#include "yhLifeUI.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"

namespace yh
{
	

	LifeUI::LifeUI() :
		  image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		std::wstring UI_path = UI_PATH;
		image = Resources::Load<Texture>(L"LifeUI", UI_path + L"Life\\LifeUI.bmp");
		sr = AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
		SetState(GameObject::eState::Pause);
	}

	LifeUI::~LifeUI()
	{

	}

	void LifeUI::Initialize()
	{
	}

	void LifeUI::Update()
	{
		GameObject::Update();
	}

	void LifeUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}