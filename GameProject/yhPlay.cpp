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

yh::Play::Play()
{
}

yh::Play::~Play()
{
}

void yh::Play::Initialize()
{

	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
	
	//배경 세팅
	BackGround* stage = object::Instantiate<BackGround>(eLayerType::Background);
	//플레이어 세팅
	Player* player = object::Instantiate<Player>(eLayerType::Player);
	//검 세팅
	PlayerSword* sword = object::Instantiate<PlayerSword>(eLayerType::Sword);

	//플레이어 초기 위치 설정
	Transform* tr = player->GetComponent<Transform>();
	tr->SetPosition(Vector2(256.0f, 256.0f));


	//배경 위치 설정
	tr = stage->GetComponent<Transform>();
	tr->SetPosition(Vector2(256.0f, 256.0f));


	//플레이어와 검 위치 같은곳으로 설정
	Vector2 sword_pos = player->GetComponent<Transform>()->GetPosition();
	sword->GetComponent<Transform>()->SetPosition(sword_pos);
	

	//배경 렌더
	SpriteRenderer* stage_sr = stage->AddComponent<SpriteRenderer>();
	Texture* image = Resources::Load<Texture>(L"stage",L"..\\Resources\\Image\\Maps\\castle_garden.png");
	stage_sr->SetImage(image);
	stage_sr->SetScale(Vector2(2.0f, 2.0f));



	//플레이어 애니메이션 세팅 이동관련
	image = Resources::Load<Texture>(L"Link"
		, L"..\\Resources\\Image\\Player\\Link_Movement\\link_main.bmp");
	Animator* at = player->AddComponent<Animator>();
	at->CreateAnimation(L"LinkForward",image,Vector2(0.0f,0.0f),Vector2(17.2f,27.0f),9,Vector2::Zero, 0.05f);
	at->CreateAnimation(L"LinkIdleDown", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
	at->CreateAnimation(L"LinkBackward", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 9, Vector2::Zero, 0.05f);
	at->CreateAnimation(L"LinkIdleUp", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
	at->CreateAnimation(L"LinkRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 11, Vector2::Zero, 0.05f);
	at->CreateAnimation(L"LinkIdleRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 1, Vector2::Zero, 0.05f);
	image = Resources::Load<Texture>(L"LinkLeftSide", L"..\\Resources\\Image\\Player\\Link_Movement\\leftside.bmp");
	at->CreateAnimation(L"LinkIdleLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 1, Vector2::Zero, 0.05f);
	at->CreateAnimation(L"LinkLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 12, Vector2::Zero, 0.05f);
	at->SetAffectedCamera(true);
	at->SetScale(Vector2(2.0f,2.0f));

	//링크 공격관련 애니메이션
	at->CreateAnimationFolder(L"LinkAttackForward", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Forward",Vector2::Zero, 0.05f);
	at->CreateAnimationFolder(L"LinkAttackBackward", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Backward", Vector2::Zero, 0.05f);
	at->CreateAnimationFolder(L"LinkAttackRight", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Right", Vector2::Zero, 0.05f);
	at->CreateAnimationFolder(L"LinkAttackLeft", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Left", Vector2::Zero, 0.05f);
	//처음 시작했을때
	at->PlayAnimation(L"LinkIdleDown");

	//검 애니메이션 세팅
	Animator* sword_anim = sword->AddComponent<Animator>();
	sword_anim->SetScale(Vector2(2.5f,2.5f));
	sword_anim->CreateAnimationFolder(L"SwordAttackForward", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Forward", Vector2(3.0f, -5.0f), 0.01f);
	sword_anim->CreateAnimationFolder(L"SwordAttackLeft", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Left", Vector2(-20.0f, 15.0f), 0.02f);
	sword_anim->CreateAnimationFolder(L"SwordAttackRight", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Right", Vector2(20.0f, 15.0f), 0.02f);
	sword_anim->CreateAnimationFolder(L"SwordAttackBackward", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Backward", Vector2(17.0f, 35.0f), 0.02f);
	
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
