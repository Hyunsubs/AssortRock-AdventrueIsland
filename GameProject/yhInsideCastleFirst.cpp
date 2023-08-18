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
#include "yhGreenKnight.h"

namespace yh
{

	InsideCastleFirst::InsideCastleFirst() :
		  stairs({})
		, steps({})
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


		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		//맵 이동 배치
		to_castle_garden = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(-0.5f, 428.0f));
		to_castle_second = object::Instantiate<MapChanger>(eLayerType::MapChanger,Vector2(389.85f, 50.0f));
		to_castle_third = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(-398.0f, 51.0f));

		//계단 단차 배치
		Stair* stair = object::Instantiate<Stair>(eLayerType::Stair, Vector2(-2.0f, -260.0f));
		stairs.push_back(stair);

		Stair* stair_second = object::Instantiate<Stair>(eLayerType::Stair, Vector2(316.0f, -125.0f));
		stairs.push_back(stair_second);

		Stair* stair_third = object::Instantiate<Stair>(eLayerType::Stair, Vector2(-322.0f, -125.0f));
		stairs.push_back(stair_second);

		Step* step_first = object::Instantiate<Step>(eLayerType::Stair, Vector2(-130.0f, -306.0f));
		step_first->SetColSize(Vector2(50.0f, 10.0f));
		steps.push_back(step_first);

		Step* step_second = object::Instantiate<Step>(eLayerType::Stair, Vector2(127.0f, -309.0f));
		step_second->SetColSize(Vector2(50.0f, 10.0f));
		steps.push_back(step_second);

		image = Resources::Load<Texture>(L"CastleFirstDownPixel", map_path + L"InsideCastle1_down.bmp");
		gn_first = object::Instantiate<GreenKnight>(eLayerType::Monster, Vector2(200.0f, 0.0f));
		gn_second = object::Instantiate<GreenKnight>(eLayerType::Monster, Vector2(-200.0f, 0.0f));
		gn_first->map_size = map_size;
		gn_first->PixelTexture = image;
		gn_second->map_size = map_size;
		gn_second->PixelTexture = image;
	}

	void InsideCastleFirst::Update()
	{
		std::wstring map_path = MAP_PATH;
		Texture * image;
		if (!(GetPlayer()->GetIsDown()))
		{
			image = Resources::Load<Texture>(L"CastleFirstUpPixel", map_path + L"InsideCastle1_up.bmp");
		}
		else
		{
			image = Resources::Load<Texture>(L"CastleFirstDownPixel", map_path + L"InsideCastle1_down.bmp");
		}

		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

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

		Vector2 player_pos = GetPlayer()->GetComponent<Transform>()->GetPosition();
		gn_first->SetChasing(true);
		gn_first->SetPlayerPos(player_pos);
		gn_second->SetChasing(true);
		gn_second->SetPlayerPos(player_pos);

		PlayerTemplate::SavePosition();
		PlayerTemplate::Save("..\\Resources\\SaveData\\status.txt");
	}

	void InsideCastleFirst::Render(HDC hdc)
	{

		PlayerTemplate::Render(hdc);
	}

}