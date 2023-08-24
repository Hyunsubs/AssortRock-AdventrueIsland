#include "yhPlayerSword.h"
#include "yhInput.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhTime.h"
#include "yhCollider.h"
#include "yhGreenKnight.h"
#include "yhMonsterTemplate.h"
#include "yhArrghusPiece.h"
#include "yhArrghus.h"
#include "yhGanon.h"
#include "yhChicken.h"

namespace yh
{
	PlayerSword::PlayerSword() :
		state(PlayerSword::SwordState::Idle),
		direction(Directions::Backward),
		get_sword(false)
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
		Chicken* chic = dynamic_cast<Chicken*>(other->GetOwner());
		if (chic != nullptr)
		{

		}
		GreenKnight* knight = dynamic_cast<GreenKnight*>(other->GetOwner());
		if (knight != nullptr)
		{
			Transform* tr = knight->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			switch (direction)
			{
			case yh::Directions::Forward:
				pos.y -= 40.0f;
				tr->SetPosition(pos);
				break;
			case yh::Directions::Backward:
				pos.y += 40.0f;
				tr->SetPosition(pos);
				break;
			case yh::Directions::Left:
				pos.x -= 40.0f;
				tr->SetPosition(pos);
				break;
			case yh::Directions::Right:
				pos.x += 40.0f;
				tr->SetPosition(pos);
				break;
			default:
				break;
			}
			int hp = knight->GetHp();
			hp -= 1;
			knight->SetHp(hp);
			return;
		}

		ArrghusPiece* ap = dynamic_cast<ArrghusPiece*>(other->GetOwner());
		if (ap != nullptr)
		{
			if (ap->GetPieceState() == PieceState::Grapped)
			{
				int hp = ap->GetHp();
				hp--;
				ap->SetHp(hp);
			}
			return;
		}

		MonsterTemplate* mt = dynamic_cast<MonsterTemplate*>(other->GetOwner());
		if (mt != nullptr)
		{
			Transform* tr = mt->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			switch (direction)
			{
			case yh::Directions::Forward:
				pos.y -= 40.0f;
				tr->SetPosition(pos);
				break;
			case yh::Directions::Backward:
				pos.y += 40.0f;
				tr->SetPosition(pos);
				break;
			case yh::Directions::Left:
				pos.x -= 40.0f;
				tr->SetPosition(pos);
				break;
			case yh::Directions::Right:
				pos.x += 40.0f;
				tr->SetPosition(pos);
				break;
			default:
				break;
			}
			int hp = mt->GetHp();
			hp -= 1;
			mt->SetHp(hp);
			return;
		}

		Arrghus* arrghus = dynamic_cast<Arrghus*>(other->GetOwner());
		if (arrghus != nullptr)
		{
			if (arrghus->GetCurPhase() == Phase::Second)
			{
				int hp = arrghus->GetHp();
				hp--;
				arrghus->SetHp(hp);
				return;
			}
		}

		Ganon* ganon = dynamic_cast<Ganon*>(other->GetOwner());
		if (ganon != nullptr)
		{
			if (ganon->GetCurPhase() == CurrentPhase::First)
			{
				int first_hp = ganon->GetFirstHp();
				first_hp--;
				ganon->SetFirstHp(first_hp);
			}
			else if (ganon->GetCurPhase() == CurrentPhase::Second)
			{
				int second_hp = ganon->GetSecondHp();
				second_hp--;
				ganon->SetSecondHp(second_hp);
			}
			return;
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
		if (Input::GetKeyDown(eKeyCode::J) && !is_Throwing && get_sword)
		{
			switch (direction)
			{
			case yh::Directions::Forward:
				sword_anim->PlayAnimation(L"SwordAttackForward", false);
				col->SetSize(Vector2(70.0f, 20.0f));
				col->SetOffset(Vector2(0.0f,-30.0f));
				break;
			case yh::Directions::Backward:
				sword_anim->PlayAnimation(L"SwordAttackBackward", false);
				col->SetSize(Vector2(70.0f, 20.0f));
				col->SetOffset(Vector2(0.0f, 30.0f));
				break;
			case yh::Directions::Left:
				sword_anim->PlayAnimation(L"SwordAttackLeft", false);
				col->SetSize(Vector2(20.0f, 70.0f));
				col->SetOffset(Vector2(-30.0f, 0.0f));
				break;
			case yh::Directions::Right:
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
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
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
			col->SetSize(Vector2(0.0f, 0.0f));
			col->SetOffset(Vector2(3000.0f,3000.0f));
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