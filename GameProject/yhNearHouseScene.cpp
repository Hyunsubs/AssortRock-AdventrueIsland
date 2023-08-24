#include "yhNearHouseScene.h"
#include "yhResources.h"
#include "yhBackGround.h"
#include "yhPlayer.h"
#include "yhMapChanger.h"
#include "yhGrass.h"
#include "yhHeartContainer.h"

namespace yh
{
	NearHouseScene::NearHouseScene() :
		  house_changer(nullptr)
		, get_sword(nullptr)
		, heart_found(false)
		, grass_manager({})
	{
	}


	NearHouseScene::~NearHouseScene()
	{
	}


	void NearHouseScene::Initialize()
	{
		std::wstring map_path = MAP_PATH;

		PlayerTemplate::Initialize();
		map_pos = (Vector2::Zero);
		map_size = Vector2(500.0f, 500.0f);
		map_scale = Vector2(2.0f, 2.0f);
		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		Texture* image = Resources::Load<Texture>(L"NearHouseBackground",map_path + L"NearHouseScene.png");
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);

		image = Resources::Load<Texture>(L"NearHousePixelCollider",map_path + L"NearHouseScene_pixel.bmp");
		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

		house_changer = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(510.0f, 313.0f));
		get_sword = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(-216.0f, -484.0f));
		
		Vector2 Grass_start = Vector2(-271.0f, 270.0f);
		Vector2 Grass_border = Vector2(32.0f, 32.0f);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				Grass* grass = object::Instantiate<Grass>(eLayerType::Grass, Vector2(Grass_start.x + (Grass_border.x * j), Grass_start.y + (Grass_border.y * i)));
				grass_manager.push_back(grass);
			}
		}
		
	}
	void NearHouseScene::Update()
	{
		if (!GetLoaded())
		{
			PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
			SetLoaded(true);
			GetPlayer()->SetState(Player::PlayerState::Idle);
		}

		house_changer->SetColliderSize(Vector2(10.0f, 100.0f));
		house_changer->SetLoadPos(Vector2(-500.0f, 300.0f));
		house_changer->SetSceneName(L"HouseScene");

		get_sword->SetColliderSize(Vector2(100.0f,10.0f));
		get_sword->SetLoadPos(Vector2(14.0f,235.0f));
		get_sword->SetSceneName(L"GetSwordScene");

		PlayerTemplate::LoadPosition();
		PlayerTemplate::Update(map_size);
		PlayerTemplate::SavePosition();
		Save("..\\Resources\\SaveData\\status.txt");

		if (!heart_found && grass_manager[7]->GetState() == GameObject::eState::Dead)
		{
			Transform* grass_tr = grass_manager[7]->GetComponent<Transform>();
			Vector2 grass_pos = grass_tr->GetPosition();
			object::Instantiate<HeartContainer>(eLayerType::Items, grass_pos);
			heart_found = true;
		}

	}


	void NearHouseScene::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}