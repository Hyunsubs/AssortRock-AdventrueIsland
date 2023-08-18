#include "yhInsideCastleThird.h"
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
	InsideCastleThird::InsideCastleThird()
	{
	}
	InsideCastleThird::~InsideCastleThird()
	{
	}
	void InsideCastleThird::Initialize()
	{
		PlayerTemplate::Initialize();

		map_pos = Vector2::Zero;
		map_size = Vector2(257.0f,488.0f);
		map_scale = Vector2(2.0f, 2.0f);

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background, map_pos);
		std::wstring map_path = MAP_PATH;
		Texture* image = Resources::Load<Texture>(L"CastleThirdImage", map_path + L"InsideCastle3.bmp");
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);


		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		//계단 배치
		Stair* stair = object::Instantiate<Stair>(eLayerType::Stair, Vector2(1.0f, 193.0f));


		//맵 전환
		to_castle_first = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(146.0f,24.0f));
	}
	void InsideCastleThird::Update()
	{
		if (!GetLoaded())
		{
			Vector2 player_pos = GetPlayer()->GetComponent<Transform>()->GetPosition();
			PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
			SetLoaded(true);
			GetPlayer()->SetState(Player::PlayerState::Idle);
		}


		to_castle_first->SetColliderSize(Vector2(15.0f, 15.0f));
		to_castle_first->SetLoadPos(Vector2(-380.0f, 51.0f));
		to_castle_first->SetSceneName(L"InsideCastleFirstScene");

		PlayerTemplate::LoadPosition();
		PlayerTemplate::Update(map_size);



		PlayerTemplate::SavePosition();
		PlayerTemplate::Save("..\\Resources\\SaveData\\status.txt");
	}
	void InsideCastleThird::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}