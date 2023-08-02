#include "yhBomb.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"

namespace yh
{
	Bomb::Bomb() :
		image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		std::wstring UI_path = UI_PATH;
		image = Resources::Load<Texture>(L"BombUI", UI_path + L"Bombs\\bomb.bmp");
		sr = AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(2.5f, 2.5f));
		SetState(GameObject::eState::Pause);
	}
	Bomb::~Bomb()
	{
	}
	void Bomb::Initialize()
	{
	}
	void Bomb::Update()
	{
		GameObject::Update();
	}
	void Bomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}