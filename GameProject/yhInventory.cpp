#include "yhInventory.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"
#include "yhTexture.h"


namespace yh
{
	Inventory::Inventory() :
		  image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		std::wstring ui_path = UI_PATH;
		sr = AddComponent<SpriteRenderer>();
		tr = GetComponent<Transform>();
		image = Resources::Load<Texture>(L"InventoryImage", ui_path + L"Inventory\\inventory.bmp");
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
		SetState(eState::Pause);
	}
	Inventory::~Inventory()
	{
	}
	void Inventory::Initialize()
	{

	}

	void Inventory::Update()
	{
		GameObject::Update();
	}
	void Inventory::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Inventory::OnCollisionEnter(Collider* other)
	{
	}
	void Inventory::OnCollisionStay(Collider* other)
	{
	}
	void Inventory::OnCollisionExit(Collider* other)
	{
	}
}