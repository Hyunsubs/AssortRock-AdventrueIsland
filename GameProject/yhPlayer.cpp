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
#include "yhSound.h"
#include "yhMana.h"
#include "yhHpInterface.h"
#include "yhPlayerShield.h"

namespace yh
{
	Player::Player()
		:state(PlayerState::Idle),
		direction(Directions::Backward),
		hp(3),
		mp(0),
		max_hp(3),
		rupee(0),
		bomb(0),
		arrow(0),
		is_dead(false),
		is_Wall(false)
	{


		Vector2 myPos = GetComponent<Transform>()->GetPosition();
		//검 인스턴스화
		sword = object::Instantiate<PlayerSword>(eLayerType::Sword, myPos);
		shield = object::Instantiate<PlayerShield>(eLayerType::Shield,myPos);
		

		//플레이어 애니메이션 세팅 이동관련
		std::wstring player_path = PLAYER_PATH;
		 Texture* image = Resources::Load<Texture>(L"LinkImage"
			, player_path + L"Link_Movement\\link_main.bmp");;

		at = AddComponent<Animator>();
		at->CreateAnimation(L"LinkForward", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 9, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleDown", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkBackward", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 9, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleUp", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 11, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 1, Vector2::Zero, 0.05f);
		image = Resources::Load<Texture>(L"LinkLeftSide", player_path + L"Link_Movement\\leftside.bmp");
		at->CreateAnimation(L"LinkIdleLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 12, Vector2::Zero, 0.05f);
		at->SetAffectedCamera(true);
		at->SetScale(Vector2(2.0f, 2.0f));

		//링크 공격관련 애니메이션
		at->CreateAnimationFolder(L"LinkAttackRight", player_path + L"Link_Movement\\Link_Attack_Right", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackLeft", player_path + L"Link_Movement\\Link_Attack_Left", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackBackward", player_path + L"Link_Movement\\Link_Attack_Backward", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackForward", player_path + L"Link_Movement\\Link_Attack_Forward", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkChargeAttackBackward", player_path + L"Link_Movement\\Link_Charge_Attack_Backward",Vector2::Zero, 0.03f);
		//링크 사망
		at->CreateAnimationFolder(L"LinkDeath", player_path + L"Link_Death", Vector2::Zero, 0.3f);
		//링크 장애물 옮기기
		at->CreateAnimationFolder(L"LinkCarrying", player_path + L"Link_Carrying", Vector2::Zero, 0.2f);
		//링크 낙사
		at->CreateAnimationFolder(L"LinkFalling", player_path + L"Link_Falling", Vector2::Zero, 0.2f);

		//링크 구조물 던지기 준비동작
		at->CreateAnimationFolder(L"LinkThrowingForwardStart", player_path + L"Link_Throwing\\Link_Throwing_Forward_Start");
		at->CreateAnimationFolder(L"LinkThrowingBackwardStart", player_path + L"Link_Throwing\\Link_Throwing_Backward_Start");
		at->CreateAnimationFolder(L"LinkThrowingLeftStart", player_path + L"Link_Throwing\\Link_Throwing_Left_Start");
		at->CreateAnimationFolder(L"LinkThrowingRightStart", player_path + L"Link_Throwing\\Link_Throwing_Right_Start");

		//링크 구조물 들고 있을때
		at->CreateAnimationFolder(L"LinkThrowingForward", player_path + L"Link_Throwing\\Link_Throwing_Forward");
		at->CreateAnimationFolder(L"LinkThrowingBackward", player_path + L"Link_Throwing\\Link_Throwing_Backward");
		at->CreateAnimationFolder(L"LinkThrowingLeft", player_path + L"Link_Throwing\\Link_Throwing_Left");
		at->CreateAnimationFolder(L"LinkThrowingRight", player_path + L"Link_Throwing\\Link_Throwing_Right");

		//링크 구조물 들고 있을때 정지
		at->CreateAnimationFolder(L"LinkThrowingForwardIdle", player_path + L"Link_Throwing\\Link_Throwing_Forward_Idle");
		at->CreateAnimationFolder(L"LinkThrowingBackwardIdle", player_path + L"Link_Throwing\\Link_Throwing_Backward_Idle");
		at->CreateAnimationFolder(L"LinkThrowingLeftIdle", player_path + L"Link_Throwing\\Link_Throwing_Left_Idle");
		at->CreateAnimationFolder(L"LinkThrowingRightIdle", player_path + L"Link_Throwing\\Link_Throwing_Right_Idle");

		//충돌판정용 Collider
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(40.0f, 30.0f));


		//링크 효과음
		AttackSound = Resources::Load<Sound>(L"BasicAttack", L"..\\Resources\\sound\\Attack\\Sword1.wav");
		Alert = Resources::Load<Sound>(L"AlertSound", L"..\\Resources\\sound\\State\\LowHP.wav");
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
		if (is_dead)
			return;
		Vector2 my_pos = GetComponent<Transform>()->GetPosition();
		Transform* tr = sword->GetComponent<Transform>();
		tr->SetPosition(my_pos);


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
		case yh::Player::PlayerState::Charge:
			Charge();
			break;
		case yh::Player::PlayerState::Throwing:
			Throwing();
			break;
		case yh::Player::PlayerState::Hit:
			Hit();
			break;
		case yh::Player::PlayerState::Ui:
			Ui();
			break;
		}

		shield->SetDirection(direction);
		
		

		if (hp <= 0)
		{
			Death();
			is_dead = true;
		}

		
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Player::OnCollisionEnter(Collider* other)
	{
		
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
		Animator* shield_anim = GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::W))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingBackward", true);
			}
			else
			{
				anim->PlayAnimation(L"LinkBackward", true);
				shield_anim->PlayAnimation(L"ShieldBackwardAnim", false);
			}
			state = PlayerState::Move;
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingLeft", true);
			}
			else
			{
				anim->PlayAnimation(L"LinkLeft", true);
				shield_anim->PlayAnimation(L"ShieldLeftAnim", false);
			}
			state = PlayerState::Move;
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingForward", true);
			}

			else
			{
				anim->PlayAnimation(L"LinkForward", true);
				shield_anim->PlayAnimation(L"ShieldForwardAnim", false);
			}

			state = PlayerState::Move;
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingRight", true);
			}
			else
			{
				anim->PlayAnimation(L"LinkRight", true);
				shield_anim->PlayAnimation(L"ShieldRightAnim", false);
			}
			state = PlayerState::Move;
			direction = Directions::Right;
		}

		if (Input::GetKeyDown(eKeyCode::J) && !is_Throwing)
		{
			state = PlayerState::Attack;
			AttackSound->Play(false);
		}

		if (Input::GetKeyDown(eKeyCode::K))
		{
			state = PlayerState::Throwing;
				
		}


	}

	void Player::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		if (!is_Wall)
		{
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
		}

		if (Input::GetKeyUp(eKeyCode::W))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingBackwardIdle", false);
			}

			else
			{
				anim->PlayAnimation(L"LinkIdleUp", false);
			}

			direction = Directions::Forward;
			state = PlayerState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingLeftIdle", false);
			}
			else
			{
				anim->PlayAnimation(L"LinkIdleLeft", false);
			}
			
			direction = Directions::Left;
			state = PlayerState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingForwardIdle", false);
			}
			else
			{
				anim->PlayAnimation(L"LinkIdleDown", false);
			}
			direction = Directions::Backward;
			state = PlayerState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingRightIdle", false);
			}
			else
			{
				anim->PlayAnimation(L"LinkIdleRight", false);
			}
			direction = Directions::Right;
			state = PlayerState::Idle;
		}
		


	}

	void Player::Attack()
	{
		Animator* anim = GetComponent<Animator>();
		switch (direction)
		{
		case yh::Directions::Forward:
			anim->PlayAnimation(L"LinkAttackForward", false);
			direction = Directions::Forward;
			break;
		case yh::Directions::Backward:
			anim->PlayAnimation(L"LinkAttackBackward", false);
			direction = Directions::Backward;
			break;
		case yh::Directions::Left:
			anim->PlayAnimation(L"LinkAttackLeft", false);
			direction = Directions::Left;
			break;
		case yh::Directions::Right:
			anim->PlayAnimation(L"LinkAttackRight", false);
			direction = Directions::Right;
			break;
		default:
			break;
		}




		state = PlayerState::Idle;


		if (Input::GetKeyDown(eKeyCode::J))
		{
			state = PlayerState::Charge;
		}
		
	}

	void Player::Death()
	{
		sword->SetSwordState(PlayerSword::SwordState::Death);
		at->PlayAnimation(L"LinkDeath", false);
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

	void Player::Throwing()
	{
		Animator* anim = GetComponent<Animator>();
		is_Throwing = !is_Throwing;

		if (!is_Throwing)
		{
			Vector2 myPos = GetComponent<Transform>()->GetPosition();
			shield = object::Instantiate<PlayerShield>(eLayerType::Shield, myPos);
			switch (direction)
			{
			case yh::Directions::Forward:
				anim->PlayAnimation(L"LinkIdleUp");
				break;
			case yh::Directions::Backward:
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Left:
				anim->PlayAnimation(L"LinkIdleLeft");
				break;
			case yh::Directions::Right:
				anim->PlayAnimation(L"LinkIdleRight");
				break;
			default:
				break;
			}
		}
		else
		{
			switch (direction)
			{
			case yh::Directions::Forward:
				anim->PlayAnimation(L"LinkThrowingBackwardStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::Backward:
				anim->PlayAnimation(L"LinkThrowingForwardStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::Left:
				anim->PlayAnimation(L"LinkThrowingLeftStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::Right:
				anim->PlayAnimation(L"LinkThrowingRightStart", false);
				is_Throwing = true;
				break;
			default:
				break;
			}
		}
		state = PlayerState::Idle;
	
	
		
	}

	void Player::Charge()
	{
		Animator* anim = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::J))
		{
			anim->PlayAnimation(L"LinkChargeAttackBackward", false);
		}

		if (Input::GetKeyUp(eKeyCode::J))
		{
			anim->PlayAnimation(L"LinkChargeAttackBackward", false);
			state = PlayerState::Idle;
		}

	}

	void Player::Hit()
	{
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
			case yh::Directions::Forward:
				pos.y += 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Backward:
				pos.y -= 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Left:
				pos.x += 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Right:
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


