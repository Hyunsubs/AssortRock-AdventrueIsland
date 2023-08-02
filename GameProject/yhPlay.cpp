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

yh::Play::Play() : player(nullptr)
{
}

yh::Play::~Play()
{
}

void yh::Play::Initialize()
{
	PlayerTemplate::Initialize();

	//��� ����
	BackGround* stage = object::Instantiate<BackGround>(eLayerType::Background,Vector2(256.0f,256.0f));


	//���� ������ ��ġ
	for (int i = 0; i < 8; i++)
	{
		object::Instantiate<ManaPoint>(eLayerType::Items,Vector2(100.0f, 140.0f + (i * 30)));
	}

	//��� ����
	SpriteRenderer* stage_sr = stage->AddComponent<SpriteRenderer>();
	Texture* image = Resources::Load<Texture>(L"stage",L"..\\Resources\\Image\\Maps\\castle_garden.png");
	stage_sr->SetImage(image);
	stage_sr->SetScale(Vector2(2.0f, 2.0f));
	stage_sr->SetAffectCamera(false);

	//�� ��ġ
	Wall* wall = object::Instantiate<Wall>(eLayerType::Wall, Vector2(400.0f, -70.0f));
	wall->SetWallSize(Vector2(50.0f,220.0f));

	//���� ��ֹ� ��ġ
	Obstacle* obstacle = object::Instantiate<Obstacle>(eLayerType::Obstacle,Vector2(100.0f,100.0f));
	Collider* col = obstacle->AddComponent<Collider>();
	col->SetSize(Vector2(30.0f,30.0f));

	//������ ��ġ
	PitFall* pit = object::Instantiate<PitFall>(eLayerType::PitFall,Vector2(400.0f,400.0f));
	col = pit->AddComponent<Collider>();
	col->SetSize(Vector2(40.0f, 40.0f));

	//��� ��ġ
	GreenKnight* knight = object::Instantiate<GreenKnight>(eLayerType::Monster, Vector2(200.0f, 200.0f));

	//���� üũ ����
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Obstacle, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::PitFall, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Sword, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Items, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
}

void yh::Play::Update()
{
	//Update�� ���� �Ķ���ͷ� �̵��ݰ� ����
	PlayerTemplate::Update(Vector2(512.0f,512.0f));
	 
}

void yh::Play::Render(HDC hdc)
{
	PlayerTemplate::Render(hdc);
}
