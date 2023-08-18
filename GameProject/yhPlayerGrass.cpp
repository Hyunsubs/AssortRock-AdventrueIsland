#include "yhPlayerGrass.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhResources.h"

namespace yh
{
	PlayerGrass::PlayerGrass() :
		  tr(nullptr)
		, sr(nullptr)
		, image(nullptr)
	{
		std::wstring tile_path = TILE_PATH;
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		image = Resources::Load<Texture>(L"PlayerGrassImage", tile_path + L"player_grass.bmp");
		sr->SetImage(image);
		sr->SetScale(Vector2::Double);
	}
	PlayerGrass::~PlayerGrass()
	{
	}
	void PlayerGrass::Initialize()
	{
	}
	void PlayerGrass::Update()
	{
		GameObject::Update();
	}
	void PlayerGrass::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}