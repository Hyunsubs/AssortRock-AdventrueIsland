#include "yhArrghusScene.h"
#include "yhPlayerTemplate.h"
#include "yhPlayer.h"
#include "yhMapChanger.h"
#include "yhTransform.h"
#include "yhObject.h"
#include "yhMapChanger.h"
#include "yhBackGround.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhCamera.h"
#include "yhArrghus.h"
#include "yhCollisionManager.h"

namespace yh
{
	ArrghusScene::ArrghusScene()
	{
	}
	ArrghusScene::~ArrghusScene()
	{
	}
	void ArrghusScene::Initialize()
	{
		std::wstring map_path = MAP_PATH;

		PlayerTemplate::Initialize();
		map_pos = (Vector2(0.0f,0.0f));
		map_size = Vector2(256.0f, 256.0f);
		map_scale = Vector2(2.0f, 2.0f);
		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background,Vector2(0.0f,0.0f));
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		Texture* image = Resources::Load<Texture>(L"ArrghusSceneImage", map_path + L"boss_map.bmp");
		bgsr->SetImage(image);
		bgsr->SetScale(map_scale);

		image = Resources::Load<Texture>(L"ArrghusScenePixelImage", map_path + L"boss_map_pixel.bmp");
		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

		boss = object::Instantiate<Arrghus>(eLayerType::Boss,Vector2(0.0f,-100.0f));
		

	}
	void ArrghusScene::Update()
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
	}
	void ArrghusScene::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}