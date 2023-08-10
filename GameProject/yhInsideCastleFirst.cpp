#include "yhInsideCastleFirst.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhPlayer.h"
#include "yhBackGround.h"
#include "yhAnimator.h"
#include "yhStair.h"
#include "yhStep.h"
#include "yhMapChanger.h"

namespace yh
{

	InsideCastleFirst::InsideCastleFirst()
	{
	}

	InsideCastleFirst::~InsideCastleFirst()
	{
	}

	void InsideCastleFirst::Initialize()
	{
		PlayerTemplate::Initialize();

		map_pos = Vector2::Zero;
		map_size = Vector2(512.0f, 512.0f);
		map_scale = Vector2(2.0f, 2.0f);

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background, map_pos);
		std::wstring map_path = MAP_PATH;

		//맵 이미지 설정
		Texture* image = Resources::Load<Texture>(L"CastleFirst", map_path + L"InsideCastle1.png");
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);


		image = Resources::Load<Texture>(L"CastleFirstPixel", map_path + L"InsideCastle1_pixel.bmp");
		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		//맵 이동 배치
		to_castle_garden = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(-0.5f, 428.0f));
		to_castle_second = object::Instantiate<MapChanger>(eLayerType::MapChanger,Vector2(389.85f, 50.0f));
		to_castle_third = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(-398.0f, 51.0f));

		//계단 단차 배치
		Stair* stair = object::Instantiate<Stair>(eLayerType::Stair, Vector2(-2.0f, -260.0f));
		Step* step = object::Instantiate<Step>(eLayerType::Stair, Vector2(-80.0f, -290.0f));
		step->SetColSize(Vector2(100.0f, 20.0f));
	}

	void InsideCastleFirst::Update()
	{
		if (!GetLoaded())
		{
			Vector2 player_pos = GetPlayer()->GetComponent<Transform>()->GetPosition();
			PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
			SetLoaded(true);
			GetPlayer()->SetState(Player::PlayerState::Idle);
		}

		to_castle_garden->SetColliderSize(Vector2(32.0f,32.0f));
		to_castle_garden->SetLoadPos(Vector2(1.0f, -430.0f));
		to_castle_garden->SetSceneName(L"CastleGardenScene");

		to_castle_second->SetColliderSize(Vector2(20.0f, 20.0f));
		to_castle_second->SetLoadPos(Vector2(-321.0f, 38.0f));
		to_castle_second->SetSceneName(L"InsideCastleSecondScene");

		to_castle_third->SetColliderSize(Vector2(20.0f, 20.0f));
		to_castle_third->SetLoadPos(Vector2(82.0f, 21.0f));
		to_castle_third->SetSceneName(L"InsideCastleThirdScene");

		PlayerTemplate::LoadPosition();
		PlayerTemplate::Update(map_size);



		PlayerTemplate::SavePosition();
		PlayerTemplate::Save("..\\Resources\\SaveData\\status.txt");
	}

	void InsideCastleFirst::Render(HDC hdc)
	{

		PlayerTemplate::Render(hdc);
	}

}