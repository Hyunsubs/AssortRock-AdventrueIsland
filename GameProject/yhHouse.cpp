#include "yhHouse.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"
#include "yhTexture.h"
#include "yhBackGround.h"
#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhPlayer.h"
#include "yhCamera.h"
#include "yhResources.h"
#include "yhAnimator.h"
#include "yhMapChanger.h"
#include "yhAsciiRender.h"
#include "yhInput.h"
#include "yhGrandpa.h"
#include "yhGrass.h"
#include "yhGreenKnight.h"
#include "yhBlueKnight.h"
#include "yhArrghus.h"
#include "yhHeartContainer.h"
#include "yhChicken.h"
#include "yhSound.h"
#include "yhBgmManager.h"

namespace yh
{
	House::House() :
		  grass_manager({})
		, heart_found(false)
		, sound_played(false)
	{
	}
	House::~House()
	{
	}

	void House::Initialize()
	{
		PlayerTemplate::Initialize();


		Transform* player_tr = PlayerTemplate::GetPlayer()->GetComponent<Transform>();
		player_tr->SetPosition(Vector2(0.0f, 0.0f));

		Vector2 map_pos = Vector2(0.0f, 0.0f);
		Vector2 map_scale = Vector2(2.0f, 2.0f);
		Vector2 map_size = Vector2(512.0f, 512.0f);

		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		//배경 세팅
		Texture* image = Resources::Load<Texture>(L"ForeLinkHouseOutside", L"..\\Resources\\Image\\Maps\\link_house.png");
		BackGround* fore_bg = object::Instantiate<BackGround>(eLayerType::ForeBackground,map_pos);
		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background, map_pos);
		BackGround* pixel_bg = object::Instantiate<BackGround>(eLayerType::PixelCollider, map_pos);
		SpriteRenderer* bgsr = fore_bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);

		image = Resources::Load<Texture>(L"LinkHouseOutside", L"..\\Resources\\Image\\Maps\\link_house.bmp");
		bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);
		
		//픽셀 충돌 설정
		std::wstring map_path = MAP_PATH;
		image = Resources::Load<Texture>(L"HousePixel", map_path + L"link_house_pixel.bmp");
		bgsr = pixel_bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);

		//맵 이동 설정
		nearhouse_map_changer = object::Instantiate<MapChanger>(eLayerType::MapChanger,Vector2(-510.0f, 300.0f));
		castle_map_changer = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(48.0f, -514.0f));
		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

		//풀 배치
		Vector2 Grass_start = Vector2(-270.0f, 53.0f);
		Vector2 Grass_border = Vector2(32.0f,32.0f);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Grass* grass = object::Instantiate<Grass>(eLayerType::Grass, Vector2(Grass_start.x + (Grass_border.x * j ), Grass_start.y + (Grass_border.y * i)));
				grass_manager.push_back(grass);
			}
		}

		Grass_start = Vector2(-436.0f, 43.0f);
		Grass_border = Vector2(32.0f, 32.0f);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Grass* grass = object::Instantiate<Grass>(eLayerType::Grass, Vector2(Grass_start.x + (Grass_border.x * j), Grass_start.y + (Grass_border.y * i)));
			}
		}

		Grass_start = Vector2(-78.0f, 439.0f);
		Grass_border = Vector2(32.0f, 32.0f);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Grass* grass = object::Instantiate<Grass>(eLayerType::Grass, Vector2(Grass_start.x + (Grass_border.x * j), Grass_start.y + (Grass_border.y * i)));
			}
		}

		//몬스터 배치
		Vector2 Monster_start = Vector2(100.0f, 300.0f);
		Vector2 Monster_border = Vector2(150.0f, 0.0f);
		for (int i = 0; i < 2; i++)
		{
			GreenKnight* gn = object::Instantiate<GreenKnight>(eLayerType::Monster, Vector2(Monster_start.x + (Monster_border.x * i), Monster_start.y + (Monster_border.y * i)));
			gn->PixelTexture = image;
			gn->map_size = map_size;
		}

		BlueKnight* bn = object::Instantiate<BlueKnight>(eLayerType::Monster, Vector2(300.0f, 300.0f));
		bn->PixelTexture = image;
		bn->map_size = map_size;


		//NPC 배치
		Grandpa* grandpa = object::Instantiate<Grandpa>(eLayerType::NPC, Vector2(-100.0f, 100.0f));


		//치킨
		chic = object::Instantiate<Chicken>(eLayerType::Chicken, Vector2(10.0f, 10.0f));
		chic->PixelTexture = image;
		chic->map_size = map_size;
		
		wstring sound_path = SOUND_PATH;


	}

	void House::Update()
	{
		if (!sound_played)
		{
			BgmManager::PlayIndexSound(BgmTypes::Main,true);
			sound_played = true;
		}

		Vector2 map_size = Vector2(512.0f, 512.0f);
		
		if (!GetLoaded())
		{
			PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
			SetLoaded(true);
			GetPlayer()->SetState(Player::PlayerState::Idle);
		}

		PlayerTemplate::LoadPosition();
		PlayerTemplate::Update(map_size);
		PlayerTemplate::Save("..\\Resources\\SaveData\\status.txt");
		PlayerTemplate::SavePosition();

		nearhouse_map_changer->SetSceneName(L"NearHouseScene");
		nearhouse_map_changer->SetColliderSize(Vector2(20.0f, 100.0f));
		nearhouse_map_changer->SetLoadPos(Vector2(480.0f, 313.0f));

		castle_map_changer->SetSceneName(L"CastleGardenScene");
		castle_map_changer->SetColliderSize(Vector2(700.0f, 10.0f));
		castle_map_changer->SetLoadPos(Vector2(850.0f, 1000.0f));
		
		Transform* player_tr = PlayerTemplate::GetPlayer()->GetComponent<Transform>();
		Vector2 cur_pos = player_tr->GetPosition();

		
		if (grass_manager[8]->GetState() == GameObject::eState::Dead && heart_found == false)
		{
			Transform* grass_tr = grass_manager[8]->GetComponent<Transform>();
			Vector2 grass_pos = grass_tr->GetPosition();
			object::Instantiate<HeartContainer>(eLayerType::Items,grass_pos);
			heart_found = true;
		}
		chic->SetPlayerPos(GetPlayer()->GetComponent<Transform>()->GetPosition());
	}

	void House::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}