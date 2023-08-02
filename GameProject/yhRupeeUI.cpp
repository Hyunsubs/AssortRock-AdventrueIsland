#include "yhRupeeUI.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"

namespace yh
{


	RupeeUI::RupeeUI() :
		image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		std::wstring UI_path = UI_PATH;
		image = Resources::Load<Texture>(L"RupeeUI", UI_path + L"Rupee\\rupee.bmp");
		sr = AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(2.5f, 2.5f));
		SetState(GameObject::eState::Pause);
	}

	RupeeUI::~RupeeUI()
	{

	}

	void RupeeUI::Initialize()
	{
	}

	void RupeeUI::Update()
	{
		GameObject::Update();
	}

	void RupeeUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}