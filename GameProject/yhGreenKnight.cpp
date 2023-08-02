#include "yhGreenKnight.h"
#include "yhAnimator.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhCollider.h"
#include "yhPlayer.h"
#include "yhTime.h"

namespace yh
{
	GreenKnight::GreenKnight() :
		state(MonsterState::Idle),
		direction(Directions::Backward),
		moving_time(2.0f),
		tr(nullptr)
	{
		std::wstring monster_path = MONSTER_PATH;
		anim = AddComponent<Animator>();
		col = AddComponent<Collider>();

		anim->CreateAnimationFolder(L"GnMovingBackward", monster_path + L"GreenKnight\\Moving\\Backward",Vector2::Zero,0.3f);
		anim->CreateAnimationFolder(L"GnMovingForward", monster_path + L"GreenKnight\\Moving\\Forward", Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"GnMovingLeft", monster_path + L"GreenKnight\\Moving\\Left", Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"GnMovingRight", monster_path + L"GreenKnight\\Moving\\Right", Vector2::Zero, 0.3f);
		col->SetSize(Vector2(30.0f, 30.0f));
		anim->SetScale(Vector2(2.0f, 2.0f));


		anim->CreateAnimationFolder(L"GnLookBackward", monster_path + L"GreenKnight\\LookAround\\Backward", Vector2::Zero, 0.15f);
		anim->CreateAnimationFolder(L"GnLookForward", monster_path + L"GreenKnight\\LookAround\\Forward", Vector2::Zero, 0.15f);
		anim->CreateAnimationFolder(L"GnLookLeft", monster_path + L"GreenKnight\\LookAround\\Left", Vector2::Zero, 0.15f);
		anim->CreateAnimationFolder(L"GnLookRight", monster_path + L"GreenKnight\\LookAround\\Right", Vector2::Zero, 0.15f);

		anim->PlayAnimation(L"GnMovingBack", false);
	}
	GreenKnight::~GreenKnight()
	{
	}
	void GreenKnight::Initialize()
	{
		
	}
	void GreenKnight::Update()
	{
		GameObject::Update();

		switch (state)
		{
		case yh::MonsterState::Idle:
			Idle();
			break;
		case yh::MonsterState::MoveReady:
			MoveReady();
			break;
		case yh::MonsterState::Move:
			Move();
			break;
		case yh::MonsterState::Attack:
			Attack();
			break;
		case yh::MonsterState::Death:
			Death();
			break;
		case yh::MonsterState::Falling:
			Falling();
			break;
		case yh::MonsterState::Ui:
			Ui();
			break;
		}
	}
	void GreenKnight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GreenKnight::OnCollisionEnter(Collider* other)
	{
		//검과 닿으면 dynamic_cast 에서 에러남
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;
		Transform* tr = player->GetComponent<Transform>();
		int player_hp = player->GetHp();
		player_hp--;
		player->SetHp(player_hp);
		player->SetState(Player::PlayerState::Hit);

		Vector2 cur_pos = tr->GetPosition();
		switch (player->GetDirection())
		{
		case Directions::Forward:
			cur_pos.y += 50.0f;
			break;
		case Directions::Backward:
			cur_pos.y -= 50.0f;
			break;
		case Directions::Left:
			cur_pos.x += 50.0f;
			break;
		case Directions::Right:
			cur_pos.x -= 50.0f;
			break;
		default:
			break;
		}
		tr->SetPosition(cur_pos);

		player->SetState(Player::PlayerState::Idle);
		
	}
	void GreenKnight::OnCollisionStay(Collider* other)
	{
	}
	void GreenKnight::OnCollisionExit(Collider* other)
	{
	}

	void GreenKnight::Idle()
	{
		switch (direction)
		{
		case yh::enums::Directions::Forward:
			anim->PlayAnimation(L"GnLookForward", false);
			break;
		case yh::enums::Directions::Backward:
			anim->PlayAnimation(L"GnLookBackward", false);
			break;
		case yh::enums::Directions::Left:
			anim->PlayAnimation(L"GnLookLeft", false);
			break;
		case yh::enums::Directions::Right:
			anim->PlayAnimation(L"GnLookRight", false);
			break;
		default:
			break;
		}

		
		state = MonsterState::MoveReady;
		
	}

	void GreenKnight::MoveReady()
	{
		if (anim->IsActiveAnimationComplete())
		{
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				anim->PlayAnimation(L"GnMovingForward", true);
				break;
			case yh::enums::Directions::Backward:
				anim->PlayAnimation(L"GnMovingBackward", true);
				break;
			case yh::enums::Directions::Left:
				anim->PlayAnimation(L"GnMovingLeft", true);
				break;
			case yh::enums::Directions::Right:
				anim->PlayAnimation(L"GnMovingRight", true);
				break;
			default:
				break;
			}
			state = MonsterState::Move;
		}


	}

	void GreenKnight::Move()
	{
		if (moving_time < 0.0f)
		{
			moving_time = 2.0f;
			state = MonsterState::Idle;
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				direction = Directions::Right;
				break;
			case yh::enums::Directions::Backward:
				direction = Directions::Left;
				break;
			case yh::enums::Directions::Left:
				direction = Directions::Forward;
				break;
			case yh::enums::Directions::Right:
				direction = Directions::Backward;
				break;
			default:
				break;
			}
		}
		else
		{
			tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			moving_time -= Time::DeltaTime();
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				pos.y -= 50.0f * Time::DeltaTime();
				break;
			case yh::enums::Directions::Backward:
				pos.y += 50.0f * Time::DeltaTime();
				break;
			case yh::enums::Directions::Left:
				pos.x -= 50.0f * Time::DeltaTime();
				break;
			case yh::enums::Directions::Right:
				pos.x += 50.0f * Time::DeltaTime();
				break;
			default:
				break;
			}
			tr->SetPosition(pos);
		}
	}

	void GreenKnight::Attack()
	{
	}

	void GreenKnight::Death()
	{
	}

	void GreenKnight::Falling()
	{
	}

	void GreenKnight::Ui()
	{
	}

	


}