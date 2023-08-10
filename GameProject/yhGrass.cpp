#include "yhGrass.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhCollider.h"
#include "yhResources.h"
#include "yhTexture.h"
#include "yhPlayer.h"



namespace yh
{
	Grass::Grass() :
		  sr(nullptr)
		, tr(nullptr)
		, image(nullptr)
		, col(nullptr)
	{

	}


	Grass::~Grass()
	{
	}


	void Grass::Initialize()
	{
		std::wstring tile_path = TILE_PATH;
		name = L"Grass";
		path = tile_path + L"grass_tile.png";

		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		col = AddComponent<Collider>();
		image = Resources::Load<Texture>(name, path);
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
		col->SetSize(Vector2(32.0f, 32.0f));
	}

	void Grass::Update()
	{
		GameObject::Update();
	}

	void Grass::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Grass::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			player->SetState(Player::PlayerState::Throwing);

		}
			
	}

	void Grass::OnCollisionStay(Collider* other)
	{
	}

	void Grass::OnCollisionExit(Collider* other)
	{
	}
}