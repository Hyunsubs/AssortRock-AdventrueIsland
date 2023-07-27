#include "yhPlayer.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhAnimator.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhGameObject.h"
#include "yhCollider.h"
#include "yhPlayerSword.h"
#include "yhObject.h"
namespace yh
{
	Player::Player()
		:state(PlayerState::Idle),
		direction(Directions::Backward),
		hp(3),
		mp(3)
	{
		//검 인스턴스화
		sword = object::Instantiate<PlayerSword>(eLayerType::Sword, GetComponent<Transform>()->GetPosition());

		//플레이어 애니메이션 세팅 이동관련
		 Texture* image = Resources::Load<Texture>(L"LinkImage"
			, L"..\\Resources\\Image\\Player\\Link_Movement\\link_main.bmp");;

		Animator* at = AddComponent<Animator>();
		at->CreateAnimation(L"LinkForward", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 9, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleDown", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkBackward", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 9, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleUp", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 11, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 1, Vector2::Zero, 0.05f);
		image = Resources::Load<Texture>(L"LinkLeftSide", L"..\\Resources\\Image\\Player\\Link_Movement\\leftside.bmp");
		at->CreateAnimation(L"LinkIdleLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 12, Vector2::Zero, 0.05f);
		at->SetAffectedCamera(true);
		at->SetScale(Vector2(2.0f, 2.0f));

		//링크 공격관련 애니메이션
		at->CreateAnimationFolder(L"LinkAttackForward", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Forward", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackBackward", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Backward", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackRight", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Right", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackLeft", L"..\\Resources\\Image\\Player\\Link_Movement\\Link_Attack_Left", Vector2::Zero, 0.02f);
		//링크 사망
		at->CreateAnimationFolder(L"LinkDeath", L"..\\Resources\\Image\\Player\\Link_Death", Vector2::Zero, 0.3f);
		//링크 장애물 옮기기
		at->CreateAnimationFolder(L"LinkCarrying", L"..\\Resources\\Image\\Player\\Link_Carrying", Vector2::Zero, 0.2f);
		//링크 낙사
		at->CreateAnimationFolder(L"LinkFalling", L"..\\Resources\\Image\\Player\\Link_Falling", Vector2::Zero, 0.2f);

		//충돌판정용 Collider
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(40.0f, 40.0f));


		//처음 시작했을때
		at->PlayAnimation(L"LinkIdleDown");
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		
	}




	void Player::Update()
	{
		GameObject::Update();

		Transform* sword_tr = sword->GetComponent<Transform>();
		sword_tr->SetPosition(GetComponent<Transform>()->GetPosition());
		switch (state)
		{
		case yh::Player::PlayerState::Idle:
			Idle();
			break;
		case yh::Player::PlayerState::Move:
			Move();
			break;
		case yh::Player::PlayerState::Attack:
			Attack();
			break;
		case yh::Player::PlayerState::Death:
			Death();
			break;
		case yh::Player::PlayerState::Falling:
			Falling();
			break;
		case yh::Player::PlayerState::Carrying:
			Carrying();
			break;
		case yh::Player::PlayerState::Map:
			Map();
			break;
		case yh::Player::PlayerState::Ui:
			Ui();
			break;
		}


		
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Player::OnCollisionEnter(Collider* other)
	{
		
		//hp--;
	}

	void Player::OnCollisionStay(Collider* other)
	{
	}

	void Player::OnCollisionExit(Collider* other)
	{
	}


	void Player::Idle()
	{
		Animator* anim = GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::W))
		{
			anim->PlayAnimation(L"LinkBackward", true);
			state = PlayerState::Move;
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			anim->PlayAnimation(L"LinkLeft", true);
			state = PlayerState::Move;
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			anim->PlayAnimation(L"LinkForward", true);
			state = PlayerState::Move;
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			anim->PlayAnimation(L"LinkRight", true);
			state = PlayerState::Move;
			direction = Directions::Right;
		}

		if (Input::GetKey(eKeyCode::J))
		{
			state = PlayerState::Attack;
		}

		if (hp <= 0)
		{
			state = PlayerState::Death;
			anim->PlayAnimation(L"LinkDeath", false);
		}

	}

	void Player::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 150.0f * Time::DeltaTime();
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 150.0f * Time::DeltaTime();
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 150.0f * Time::DeltaTime();
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 150.0f * Time::DeltaTime();
			direction = Directions::Right;
		}
		tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::W))
		{
			anim->PlayAnimation(L"LinkIdleUp", false);
			state = PlayerState::Idle;
			direction = Directions::Forward;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			anim->PlayAnimation(L"LinkIdleLeft", false);
			state = PlayerState::Idle;
			direction = Directions::Left;
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			anim->PlayAnimation(L"LinkIdleDown", false);
			state = PlayerState::Idle;
			direction = Directions::Backward;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			anim->PlayAnimation(L"LinkIdleRight", false);
			state = PlayerState::Idle;
			direction = Directions::Right;
		}

		if (hp <= 0)
		{
			state = PlayerState::Death;
			anim->PlayAnimation(L"LinkDeath", false);
		}
	}

	void Player::Attack()
	{
		Animator* anim = GetComponent<Animator>();
		switch (direction)
		{
		case yh::Player::Directions::Forward:
			anim->PlayAnimation(L"LinkAttackForward", false);
			direction = Directions::Forward;
			break;
		case yh::Player::Directions::Backward:
			anim->PlayAnimation(L"LinkAttackBackward", false);
			direction = Directions::Backward;
			break;
		case yh::Player::Directions::Left:
			anim->PlayAnimation(L"LinkAttackLeft", false);
			direction = Directions::Left;
			break;
		case yh::Player::Directions::Right:
			anim->PlayAnimation(L"LinkAttackRight", false);
			direction = Directions::Right;
			break;
		default:
			break;
		}
		state = PlayerState::Idle;
		
		if (hp <= 0)
		{
			state = PlayerState::Death;
			anim->PlayAnimation(L"LinkDeath", false);
		}

	}

	void Player::Death()
	{
		
		
	}

	void Player::Map()
	{
	}

	void Player::Carrying()
	{
		Animator* anim = GetComponent<Animator>();
		if (anim->IsActiveAnimationComplete())
			state = PlayerState::Idle;
	}

	void Player::Falling()
	{
		Animator* anim = GetComponent<Animator>();
		if (anim->IsActiveAnimationComplete())
		{
			hp--;
			state = PlayerState::Idle;
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			switch (direction)
			{
			case yh::Player::Directions::Forward:
				pos.y += 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Player::Directions::Backward:
				pos.y -= 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Player::Directions::Left:
				pos.x += 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Player::Directions::Right:
				pos.x -= 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			default:
				break;
			}
		}

	}

	void Player::Ui()
	{
	}

	




}


