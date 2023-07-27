#include "yhTile.h"
#include "yhSpriteRenderer.h"
#include "yhCollider.h"
#include "yhTexture.h"
#include "yhResources.h"

namespace yh
{
	UINT Tile::mSelectedX = 0;
	UINT Tile::mSelectedY = 0;

	Tile::Tile()
		: mSpriteRenderer(nullptr)
	{
	}

	Tile::~Tile()
	{
	}

	void Tile::Initialize()
	{
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		//AddComponent<Collider>();

		yh::Texture* springFloor
			= yh::Resources::Find<yh::Texture>(L"SprintFloorTile");

		mSpriteRenderer->SetImage(springFloor);
		mSpriteRenderer->SetScale(Vector2(3.0f, 3.0f));
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Tile::SetTile(int x, int y)
	{
		mSpriteRenderer->SetTile(x, y);
	}
}