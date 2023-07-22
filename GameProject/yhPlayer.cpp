#include "yhPlayer.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhAnimator.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhGameObject.h"

namespace yh
{
	Player::Player()
		:state(PlayerState::Idle),
		direction(Directions::Backward)
	{
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
	}

	void Player::Death()
	{
	}

	void Player::Map()
	{
	}

	void Player::Falling()
	{
	}

	void Player::Ui()
	{
	}




}


