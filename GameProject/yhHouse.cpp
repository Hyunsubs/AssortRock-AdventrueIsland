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


namespace yh
{
	House::House()
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
		
		
	}

	void House::Update()
	{

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


	}

	void House::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}