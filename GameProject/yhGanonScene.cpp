#include "yhGanonScene.h"
#include "yhPlayer.h"
#include "yhBackGround.h"
#include "yhResources.h"
#include "yhCamera.h"
#include "yhGanon.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhZelda.h"
#include "yhAnimator.h"

namespace yh
{
	GanonScene::GanonScene() :
		  cur_alpha(1.0f)
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
		bgsr = bg->AddComponent<SpriteRenderer>();
		Texture* image = Resources::Load<Texture>(L"GanonSceneImage", map_path + L"ganon_map.bmp");
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);

		image = Resources::Load<Texture>(L"GanonScenePixelImage", map_path + L"ganon_map_pixel.bmp");
		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

		boss = object::Instantiate<Ganon>(eLayerType::Boss, Vector2(-18.0f,-85.0f));

		first_talking = false;
		second_talking = false;

		zelda = object::Instantiate<Zelda>(eLayerType::NPC, Vector2(0.0f, 0.0f));
		zelda->SetState(GameObject::eState::Pause);
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
			Animator* player_anim = GetPlayer()->GetComponent<Animator>();
			player_anim->PlayAnimation(L"LinkIdleUp", false);
			first_talking = true;
		}


		if (boss->GetCurPhase() == CurrentPhase::SecondTalking && !second_talking)
		{
			boss->GetPlayer(GetPlayer());
			GetPlayer()->SetState(Player::PlayerState::Talking);
			second_talking = true;
		}


		if (boss->GetState() == GameObject::eState::Dead)
		{
			cur_alpha -= 0.1f * Time::DeltaTime();
			bgsr->SetAlpha(cur_alpha);
			
		}

		if (cur_alpha <= 0.0f)
		{
			SceneManager::LoadScene(L"EndingScene");
			
		}

	}
	void GanonScene::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}