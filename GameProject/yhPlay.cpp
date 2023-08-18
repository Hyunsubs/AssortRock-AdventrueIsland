#include "yhPlay.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhObject.h"
#include "yhInput.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhObject.h"
#include "yhInput.h"
#include "yhTexture.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhBackGround.h"
#include "yhCamera.h"
#include "yhAnimator.h"
#include "yhSceneChanger.h"
#include "yhCollider.h"
#include "yhPlayerSword.h"
#include "yhCollisionManager.h"
#include "yhObstacle.h"
#include "yhPitFall.h"
#include "yhRigidbody.h"
#include "yhGreenKnight.h"
#include "yhManaPoint.h"
#include "yhMana.h"
#include "yhWall.h"
#include "yhHpInterface.h"
#include "yhMapChanger.h"
#include "yhGrass.h"


yh::Play::Play()
{
}

yh::Play::~Play()
{
}

void yh::Play::Initialize()
{
	PlayerTemplate::Initialize();

	map_pos = Vector2(0.0f, 0.0f);
	map_scale = Vector2(2.0f, 2.0f);
	map_size = Vector2(1024.0f, 1025.0f);
	//배경 세팅
	BackGround* stage = object::Instantiate<BackGround>(eLayerType::Background, map_pos);
	
	Transform* player_tr = PlayerTemplate::GetPlayer()->GetComponent<Transform>();
	player_tr->SetPosition(Vector2(850.0f, 1000.0f));

	//마나 아이템 배치
	for (int i = 0; i < 8; i++)
	{
		object::Instantiate<ManaPoint>(eLayerType::Items,Vector2(700.0f, 140.0f + (i * 30)));
	}

	//배경 렌더
	SpriteRenderer* stage_sr = stage->AddComponent<SpriteRenderer>();
	Texture* image = Resources::Load<Texture>(L"stage",L"..\\Resources\\Image\\Maps\\castle_garden.png");
	stage_sr->SetImage(image);
	stage_sr->SetScale(map_scale);
	stage_sr->SetAffectCamera(false);

	

	//벽 배치
	Wall* wall = object::Instantiate<Wall>(eLayerType::Wall, Vector2(400.0f, -70.0f));
	wall->SetWallSize(Vector2(50.0f,220.0f));



	//기사 배치
	knight = object::Instantiate<GreenKnight>(eLayerType::Monster, Vector2(800.0f, 900.0f));


	//픽셀 충돌 설정
	std::wstring map_path = MAP_PATH;
	image = Resources::Load<Texture>(L"CastleGardenPixel", map_path + L"castle_garden_pixel.bmp");

	GetPlayer()->PixelTexture = image;
	GetPlayer()->map_size = map_size;
	knight->PixelTexture = image;
	knight->map_size = map_size;

	Vector2 grass_start = Vector2(308.0f, 338.0f);
	Vector2 grass_border = Vector2(32.0f, 32.0f);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Grass* grass = object::Instantiate<Grass>(eLayerType::Grass, Vector2(grass_start.x + (grass_border.x * j), grass_start.y + (grass_border.y * i)));
		}
	}

	//맵 이동 배치
	castle_to_house = object::Instantiate<MapChanger>(eLayerType::MapChanger,Vector2(850.0f, 1060.0f));
	inside_castle = object::Instantiate<MapChanger>(eLayerType::MapChanger,Vector2(789.0f,-689.0f));
	inside_castle2 = object::Instantiate<MapChanger>(eLayerType::MapChanger, Vector2(4.0f, -467.0f));
}

void yh::Play::Update()
{
	if (!GetLoaded())
	{
		PlayerTemplate::Load("..\\Resources\\SaveData\\status.txt");
		SetLoaded(true);
		GetPlayer()->SetState(Player::PlayerState::Idle);
	}

	castle_to_house->SetColliderSize(Vector2(800.0f, 10.0f));
	castle_to_house->SetLoadPos(Vector2(48.0f, -490.0f));
	castle_to_house->SetSceneName(L"HouseScene");

	inside_castle->SetColliderSize(Vector2(16.0f, 16.0f));
	inside_castle->SetLoadPos(Vector2(0.0f, -0.0f));
	inside_castle->SetSceneName(L"InsideCastleFirstScene");

	inside_castle2->SetColliderSize(Vector2(10.0f,10.0f));
	inside_castle2->SetLoadPos(Vector2(0.0f,408.0f));
	inside_castle2->SetSceneName(L"InsideCastleFirstScene");

	PlayerTemplate::SetMapPos(map_pos);
	PlayerTemplate::SetMapScale(map_scale);
	PlayerTemplate::LoadPosition();
	//Update에 들어가는 파라미터로 이동반경 제한
	PlayerTemplate::Update(map_size);

	PlayerTemplate::SavePosition();
	Vector2 player_pos = PlayerTemplate::GetPlayerPos();
	Transform* knight_tr = knight->GetComponent<Transform>();
	Vector2 knight_pos = knight_tr->GetPosition();

	if (abs(player_pos.x - knight_pos.x) <= 200.0f && abs(player_pos.y - knight_pos.y) <= 200.0f && !(GetPlayer()->GetIsDead()))
	{
		knight->SetChasing(true);
		knight->SetPlayerPos(player_pos);
	}
	else
	{
		knight->SetChasing(false);
	}

	PlayerTemplate::Save("..\\Resources\\SaveData\\status.txt");
}



void yh::Play::Render(HDC hdc)
{
	PlayerTemplate::Render(hdc);

}
