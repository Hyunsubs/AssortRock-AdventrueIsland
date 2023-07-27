#include "yhPlayerSword.h"
#include "yhInput.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhTime.h"
#include "yhCollider.h"
#include "yhGreenKnight.h"

namespace yh
{
	PlayerSword::PlayerSword() :
		state(PlayerSword::SwordState::Idle),
		direction(Directions::Backward)
	{
		//검 애니메이션 세팅
		sword_anim = AddComponent<Animator>();
		col = AddComponent<Collider>();
		sword_anim->SetScale(Vector2(2.0f,2.0f));
		sword_anim->CreateAnimationFolder(L"SwordAttackForward", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Forward", Vector2(0.0f, -15.0f), 0.01f);
		sword_anim->CreateAnimationFolder(L"SwordAttackLeft", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Left", Vector2(-15.0f, 10.0f), 0.01f);
		sword_anim->CreateAnimationFolder(L"SwordAttackRight", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Right", Vector2(15.0f, 10.0f), 0.01f);
		sword_anim->CreateAnimationFolder(L"SwordAttackBackward", L"..\\Resources\\Image\\Player\\Link_Sword\\Sword_Attack_Backward", Vector2(0.0f, 15.0f), 0.01f);
	
		
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
	void PlayerSword::OnCollisionEnter(Collider* other)
	{
		GreenKnight* knight = dynamic_cast<GreenKnight*>(other->GetOwner());
		Transform* tr = knight->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		switch (direction)
		{
		case yh::PlayerSword::Directions::Forward:
			pos.y -= 10.0f;
			tr->SetPosition(pos);
			break;
		case yh::PlayerSword::Directions::Backward:
			pos.y += 10.0f;
			tr->SetPosition(pos);
			break;
		case yh::PlayerSword::Directions::Left:
			pos.x -= 10.0f;
			tr->SetPosition(pos);
			break;
		case yh::PlayerSword::Directions::Right:
			pos.x += 10.0f;
			tr->SetPosition(pos);
			break;
		case yh::PlayerSword::Directions::None:
			break;
		default:
			break;
		}
	}
	void PlayerSword::OnCollisionStay(Collider* other)
	{
	}
	void PlayerSword::OnCollisionExit(Collider* other)
	{
	}
	void PlayerSword::Idle()
	{
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
				sword_anim->PlayAnimation(L"SwordAttackForward", false);
				col->SetSize(Vector2(70.0f, 20.0f));
				col->SetOffset(Vector2(0.0f,-30.0f));
				break;
			case yh::PlayerSword::Directions::Backward:
				sword_anim->PlayAnimation(L"SwordAttackBackward", false);
				col->SetSize(Vector2(70.0f, 20.0f));
				col->SetOffset(Vector2(0.0f, 30.0f));
				break;
			case yh::PlayerSword::Directions::Left:
				sword_anim->PlayAnimation(L"SwordAttackLeft", false);
				col->SetSize(Vector2(20.0f, 70.0f));
				col->SetOffset(Vector2(-30.0f, 0.0f));
				break;
			case yh::PlayerSword::Directions::Right:
				sword_anim->PlayAnimation(L"SwordAttackRight", false);
				col->SetSize(Vector2(20.0f, 70.0f));
				col->SetOffset(Vector2(30.0f, 0.0f));
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
			//pos.y -= 150.0f * Time::DeltaTime();
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			//pos.x -= 150.0f * Time::DeltaTime();
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			//pos.y += 150.0f * Time::DeltaTime();
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			//pos.x += 150.0f * Time::DeltaTime();
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
		Animator* anim = GetComponent<Animator>();
		Collider* col = GetComponent<Collider>();
		if (anim->IsActiveAnimationComplete())
		{
			col->SetSize(Vector2(0.0f, 20.0f));
			col->SetOffset(Vector2::Zero);
			state = SwordState::Idle;
		}
		
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