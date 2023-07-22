#include "yhPlayerSword.h"
#include "yhInput.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhTime.h"


namespace yh
{
	PlayerSword::PlayerSword() :
		state(PlayerSword::SwordState::Idle)
	{
	}
	PlayerSword::~PlayerSword()
	{
	}
	void PlayerSword::Initialize()
	{
	}
	void PlayerSword::Update()
	{
		GameObject::Update();

		switch (state)
		{
		case yh::PlayerSword::SwordState::Idle:
			Idle();
			break;
		case yh::PlayerSword::SwordState::Move:
			Move();
			break;
		case yh::PlayerSword::SwordState::Attack:
			Attack();
			break;
		case yh::PlayerSword::SwordState::Death:
			Death();
			break;
		case yh::PlayerSword::SwordState::Falling:
			Falling();
			break;
		case yh::PlayerSword::SwordState::Map:
			Map();
			break;
		case yh::PlayerSword::SwordState::Ui:
			Ui();
			break;
		}

	}
	void PlayerSword::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}
	void PlayerSword::Idle()
	{
		Animator* anim = GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::W))
		{
			state = SwordState::Move;
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			state = SwordState::Move;
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			state = SwordState::Move;
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			state = SwordState::Move;
			direction = Directions::Right;
		}
		if (Input::GetKey(eKeyCode::J))
		{
			switch (direction)
			{
			case yh::PlayerSword::Directions::Forward:
				anim->PlayAnimation(L"SwordAttackForward", false);
				break;
			case yh::PlayerSword::Directions::Backward:
				anim->PlayAnimation(L"SwordAttackBackward", false);
				break;
			case yh::PlayerSword::Directions::Left:
				anim->PlayAnimation(L"SwordAttackLeft", false);
				break;
			case yh::PlayerSword::Directions::Right:
				anim->PlayAnimation(L"SwordAttackRight", false);
				break;
			default:
				break;
			}
			state = SwordState::Attack;
		}

	}
	void PlayerSword::Move()
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
			direction = Directions::Forward;
			state = SwordState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			anim->PlayAnimation(L"LinkIdleLeft", false);
			direction = Directions::Left;
			state = SwordState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			anim->PlayAnimation(L"LinkIdleDown", false);
			direction = Directions::Backward;
			state = SwordState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			anim->PlayAnimation(L"LinkIdleRight", false);
			direction = Directions::Right;
			state = SwordState::Idle;
		}
	}
	void PlayerSword::Attack()
	{
		state = SwordState::Idle;
	}
	void PlayerSword::Death()
	{
	}
	void PlayerSword::Map()
	{
	}
	void PlayerSword::Falling()
	{
	}
	void PlayerSword::Ui()
	{
	}
}