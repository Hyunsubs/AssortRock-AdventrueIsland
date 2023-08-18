#include "yhEmptyGrass.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"


namespace yh
{
	EmptyGrass::EmptyGrass() :
		  tr(nullptr)
		, image(nullptr)
		, sr(nullptr)
	{
		std::wstring tile_path = TILE_PATH;
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		image = Resources::Load<Texture>(L"EmptyGrassImage",tile_path + L"grass_throw_tile.png");
		sr->SetImage(image);
		sr->SetScale(Vector2::Double);
	}
	EmptyGrass::~EmptyGrass()
	{
	}
	void EmptyGrass::Initialize()
	{
	}
	void EmptyGrass::Update()
	{
		GameObject::Update();
	}
	void EmptyGrass::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}