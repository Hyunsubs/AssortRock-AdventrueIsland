#include "yhCurItem.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"

namespace yh
{
	CurItem::CurItem() :
		image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		std::wstring UI_path = UI_PATH;
		image = Resources::Load<Texture>(L"CurItemUI", UI_path + L"CurItem\\CurItem.bmp");
		sr = AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
		SetState(GameObject::eState::Pause);
	}
	CurItem::~CurItem()
	{
	}
	void CurItem::Initialize()
	{
	}
	void CurItem::Update()
	{
		GameObject::Update();
	}
	void CurItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}