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

yh::Play::Play() :
	sword(nullptr)
{
}

yh::Play::~Play()
{
}

void yh::Play::Initialize()
{
	//ȭ�� ���氡���� ��ü����
	object::Instantiate<SceneChanger>(eLayerType::Background);
	//��� ����
	BackGround* stage = object::Instantiate<BackGround>(eLayerType::Background);
	//�÷��̾� ����
	Player* player = object::Instantiate<Player>(eLayerType::Player);

	//�÷��̾� �ʱ� ��ġ ����
	Transform* tr = player->GetComponent<Transform>();
	tr->SetPosition(Vector2(256.0f, 256.0f));


	//��� ��ġ ����
	tr = stage->GetComponent<Transform>();
	tr->SetPosition(Vector2(256.0f, 256.0f));


	//��� ����
	SpriteRenderer* stage_sr = stage->AddComponent<SpriteRenderer>();
	Texture* image = Resources::Load<Texture>(L"stage",L"..\\Resources\\Image\\Maps\\castle_garden.png");
	stage_sr->SetImage(image);
	stage_sr->SetScale(Vector2(2.0f, 2.0f));

	

	//���� ��ֹ� ��ġ
	Obstacle* obstacle = object::Instantiate<Obstacle>(eLayerType::Obstacle);
	tr = obstacle->GetComponent<Transform>();
	tr->SetPosition(Vector2(100.0f, 100.0f));
	Collider* col = obstacle->AddComponent<Collider>();
	col->SetSize(Vector2(30.0f,30.0f));

	//������ ��ġ
	PitFall* pit = object::Instantiate<PitFall>(eLayerType::PitFall);
	tr = pit->GetComponent<Transform>();
	tr->SetPosition(Vector2(400.0f, 400.0f));
	col = pit->AddComponent<Collider>();
	col->SetSize(Vector2(40.0f, 40.0f));

	GreenKnight* knight = object::Instantiate<GreenKnight>(eLayerType::Monster);
	tr = knight->GetComponent<Transform>();
	tr->SetPosition(Vector2(200.0f, 200.0f));

	//���� üũ ����
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Obstacle, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::PitFall, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
	CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Sword, true);
	Camera::SetTarget(player);
}

void yh::Play::Update()
{
	Scene::Update();
}

void yh::Play::Render(HDC hdc)
{
	Scene::Render(hdc);
}
