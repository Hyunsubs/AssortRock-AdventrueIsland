#include "yhGanonScene.h"
#include "yhPlayer.h"
#include "yhBackGround.h"
#include "yhResources.h"
#include "yhCamera.h"
#include "yhGanon.h"
#include "yhInput.h"

namespace yh
{
	GanonScene::GanonScene()
	{
	}
	GanonScene::~GanonScene()
	{
	}
	void GanonScene::Initialize()
	{
		std::wstring map_path = MAP_PATH;

		PlayerTemplate::Initialize();
		map_pos = (Vector2(0.0f, 0.0f));
		map_size = Vector2(512.0f, 256.0f);
		map_scale = Vector2(2.0f, 2.0f);
		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background, Vector2(0.0f, 0.0f));
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		Texture* image = Resources::Load<Texture>(L"GanonSceneImage", map_path + L"ganon_map.bmp");
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);

		image = Resources::Load<Texture>(L"GanonScenePixelImage", map_path + L"ganon_map_pixel.bmp");
		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

		boss = object::Instantiate<Ganon>(eLayerType::Boss, Vector2(-18.0f,-85.0f));

		first_talking = false;
		second_talking = false;

	}
	void GanonScene::Update()
	{
		if (!GetLoaded())
		{
			PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
			SetLoaded(true);
			GetPlayer()->SetState(Player::PlayerState::Idle);
			Camera::SetLookPosition(Vector2::Zero);
		}

		PlayerTemplate::LoadPosition();
		PlayerTemplate::Update(map_size);
		PlayerTemplate::Save("..\\Resources\\SaveData\\status.txt");
		PlayerTemplate::SavePosition();

		Transform* player_tr = GetPlayer()->GetComponent<Transform>();
		boss->SetPlayerPos(player_tr->GetPosition());

		if (boss->GetCurPhase() == CurrentPhase::FirstTalking && !first_talking)
		{
			boss->GetPlayer(GetPlayer());
			GetPlayer()->SetState(Player::PlayerState::Talking);
			first_talking = true;
		}


		if (boss->GetCurPhase() == CurrentPhase::SecondTalking && !second_talking)
		{
			boss->GetPlayer(GetPlayer());
			GetPlayer()->SetState(Player::PlayerState::Talking);
			second_talking = true;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			int hp = boss->GetFirstHp();
			hp--;
			boss->SetFirstHp(hp);
		}
	}
	void GanonScene::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}