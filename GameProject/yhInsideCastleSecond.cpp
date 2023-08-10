#include "yhInsideCastleSecond.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhPlayer.h"
#include "yhBackGround.h"
#include "yhAnimator.h"
#include "yhStair.h"

namespace yh
{
	InsideCastleSecond::InsideCastleSecond()
	{
	}
	InsideCastleSecond::~InsideCastleSecond()
	{
	}
	void InsideCastleSecond::Initialize()
	{
		PlayerTemplate::Initialize();

		map_pos = Vector2::Zero;
		map_size = Vector2(472.0f, 505.0f);
		map_scale = Vector2(2.0f, 2.0f);

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background, map_pos);
		std::wstring map_path = MAP_PATH;
		Texture* image = Resources::Load<Texture>(L"InsideCastle2", map_path + L"InsideCastle2.png");
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);

		GetPlayer()->GetComponent<Transform>()->SetPosition(Vector2(20.0f, 20.0f));


		PlayerTemplate::GetPlayer()->map_size = map_size;
		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		//픽셀 충돌 설정
		Texture* down_pixel_image = Resources::Load<Texture>(L"InsideCastle2downPixel", map_path + L"InsideCastle2down.bmp");
		PlayerTemplate::GetPlayer()->PixelTexture = down_pixel_image;
		PlayerTemplate::GetPlayer()->map_size = map_size;

		//계단 배치
		Stair* stair = object::Instantiate<Stair>(eLayerType::Stair, Vector2(125.0f, -214.0f));

	}
	void InsideCastleSecond::Update()
	{
		if (!GetLoaded())
		{
			Vector2 player_pos = GetPlayer()->GetComponent<Transform>()->GetPosition();
			PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
			SetLoaded(true);
			GetPlayer()->SetState(Player::PlayerState::Idle);
		}
		PlayerTemplate::LoadPosition();
		PlayerTemplate::Update(map_size);


		Vector2 player_pos = GetPlayer()->GetComponent<Transform>()->GetPosition();
		std::wstring map_path = MAP_PATH;

		bool is_Down = GetPlayer()->GetIsDown();
		if (is_Down)
		{
			Texture* down_pixel_image = Resources::Load<Texture>(L"InsideCastle2downPixel", map_path + L"InsideCastle2down.bmp");
			PlayerTemplate::GetPlayer()->PixelTexture = down_pixel_image;
			if (player_pos.x > -80.0f && player_pos.x < 10.0f && player_pos.y > -175.0f && player_pos.y < 100.0f)
			{
				GetPlayer()->SetBridge(true);
			}
			else
			{
				GetPlayer()->SetBridge(false);
			}
		}

		else
		{

			Texture* up_pixel_image = Resources::Load<Texture>(L"InsideCastle2upPixel", map_path + L"InsideCastle2_up.bmp");
			PlayerTemplate::GetPlayer()->PixelTexture = up_pixel_image;
		}


		PlayerTemplate::SavePosition();
		PlayerTemplate::Save("..\\Resources\\SaveData\\status.txt");
	
	}

	void InsideCastleSecond::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}