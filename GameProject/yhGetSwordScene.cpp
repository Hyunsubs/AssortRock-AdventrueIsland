#include "yhGetSwordScene.h"
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


namespace yh
{
	GetSwordScene::GetSwordScene() :
		  map_pos(Vector2::Zero)
		, map_scale(Vector2(2.0f,2.0f))
		, map_size(Vector2(256.0f,260.0f))
		, to_near_house(nullptr)
	{
	}
	GetSwordScene::~GetSwordScene()
	{
	}
	void GetSwordScene::Initialize()
	{
		std::wstring map_path = MAP_PATH;
		PlayerTemplate::Initialize();

		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background,map_pos);
		to_near_house = object::Instantiate<MapChanger>(eLayerType::MapChanger,Vector2(14.0f,255.0f));

		Texture* image = Resources::Load<Texture>(L"GetSwordSceneImage", map_path + L"sword_get_scene.bmp");
		SpriteRenderer* sr = bg->AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(map_scale);
		
		PlayerTemplate::SetMapPos(map_pos);
		PlayerTemplate::SetMapScale(map_scale);

		
		//픽셀 충돌 설정
		image = Resources::Load<Texture>(L"GetSwordScenePixelImage", map_path + L"sword_get_scene_pixel.bmp");
		GetPlayer()->PixelTexture = image;
		GetPlayer()->map_size = map_size;

		to_near_house->SetColliderSize(Vector2(300.0f,10.0f));
		to_near_house->SetLoadPos(Vector2(-216.0f, -464.0f));
	}

	void GetSwordScene::Update()
	{
		to_near_house->SetSceneName(L"NearHouseScene");
		if (!GetLoaded())
		{
			Vector2 player_pos = GetPlayer()->GetComponent<Transform>()->GetPosition();
			PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
			SetLoaded(true);
			GetPlayer()->SetState(Player::PlayerState::Idle);
		}
		PlayerTemplate::LoadPosition();
		Load("..\\Resources\\SaveData\\status.txt");
		PlayerTemplate::Update(map_size);
		PlayerTemplate::SavePosition();
		Save("..\\Resources\\SaveData\\status.txt");

	}
	void GetSwordScene::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}