#include "yhBlueKnight.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhCollider.h"
#include "yhResources.h"
#include "yhObject.h"
#include "yhTime.h"
#include "yhPlayer.h"
#include "yhObject.h"
#include "yhArrowProjectile.h"
#include "yhSound.h"

namespace yh
{
	BlueKnight::BlueKnight() :
		  move_time(2.0f)
		, freeze_time(1.5f)
		, direct(Directions::Backward)
		, state(MonsterState::Idle)
	{
		std::wstring monster_path = MONSTER_PATH;
		anim = AddComponent<Animator>();
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();
		col->SetSize(Vector2(20.0f, 32.0f));

		//파랑 기사 기본 움직임
		anim->CreateAnimationFolder(L"BnMovingBackward", monster_path + L"BlueKnight\\Moving\\Backward",Vector2::Zero,0.3f);
		anim->CreateAnimationFolder(L"BnMovingForward", monster_path + L"BlueKnight\\Moving\\Forward", Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"BnMovingLeft", monster_path + L"BlueKnight\\Moving\\Left", Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"BnMovingRight", monster_path + L"BlueKnight\\Moving\\Right", Vector2::Zero, 0.3f);

		//공격 모션
		anim->CreateAnimationFolder(L"BnAttackBackward", monster_path + L"BlueKnight\\Attack\\Backward", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"BnAttackForward", monster_path + L"BlueKnight\\Attack\\Forward", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"BnAttackLeft", monster_path + L"BlueKnight\\Attack\\Left", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"BnAttackRight", monster_path + L"BlueKnight\\Attack\\Right", Vector2::Zero, 0.1f);

		//사망모션
		anim->CreateAnimationFolder(L"BnDeath", monster_path + L"BlueKnight\\Dead", Vector2::Zero, 0.3f);
		anim->SetScale(Vector2::Double);
		SetHp(2);

		wstring sound_path = SOUND_PATH;
		death_sound = Resources::Load<Sound>(L"DeadSound", sound_path + L"break.wav");

	}
	BlueKnight::~BlueKnight()
	{
	}
	void BlueKnight::Initialize()
	{
	}
	void BlueKnight::Update()
	{
		MonsterTemplate::Update();
		int hp = GetHp();

		if (hp <= 0 && state != MonsterState::Death)
		{
			anim->PlayAnimation(L"BnDeath", false);
			death_sound->Play(false);
			state = MonsterState::Death;
		}

		switch (state)
		{
		case yh::MonsterState::Idle:
			Idle();
			break;
		case yh::MonsterState::Move:
			Move();
			break;
		case yh::MonsterState::Attack:
			Attack();
			break;
		case yh::MonsterState::Death:
			MonsterTemplate::Death();
			break;
		case yh::MonsterState::Freeze:
			Freeze();
			break;
		default:
			break;
		}
	}
	void BlueKnight::Render(HDC hdc)
	{
		MonsterTemplate::Render(hdc);
	}
	void BlueKnight::OnCollisionEnter(Collider* other)
	{
		MonsterTemplate::OnCollisionEnter(other);
		
	}
	void BlueKnight::OnCollisionStay(Collider* other)
	{
	}
	void BlueKnight::OnCollisionExit(Collider* other)
	{
	}
	void BlueKnight::Idle()
	{
		switch (direct)
		{
		case yh::enums::Directions::Forward:
			anim->PlayAnimation(L"BnMovingForward", true);
			break;
		case yh::enums::Directions::Backward:
			anim->PlayAnimation(L"BnMovingBackward", true);
			break;
		case yh::enums::Directions::Left:
			anim->PlayAnimation(L"BnMovingLeft", true);
			break;
		case yh::enums::Directions::Right:
			anim->PlayAnimation(L"BnMovingRight", true);
			break;
		case yh::enums::Directions::End:
			break;
		default:
			break;
		}

		state = MonsterState::Move;
	}
	void BlueKnight::Move()
	{
		move_time -= Time::DeltaTime();
		Vector2 cur_pos = tr->GetPosition();

		switch (direct)
		{
		case yh::enums::Directions::Forward:
			cur_pos.y -= 70.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Backward:
			cur_pos.y += 70.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Left:
			cur_pos.x -= 70.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Right:
			cur_pos.x += 70.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::End:
			break;
		default:
			break;
		}
		tr->SetPosition(cur_pos);

		if (move_time <= 0.0f)
		{
			move_time = 2.0f;
			state = MonsterState::Attack;
		}

	}
	void BlueKnight::Attack()
	{
		switch (direct)
		{
		case yh::enums::Directions::Forward:
			anim->PlayAnimation(L"BnAttackForward", false);
			break;
		case yh::enums::Directions::Backward:
			anim->PlayAnimation(L"BnAttackBackward", false);
			break;
		case yh::enums::Directions::Left:
			anim->PlayAnimation(L"BnAttackLeft", false);
			break;
		case yh::enums::Directions::Right:
			anim->PlayAnimation(L"BnAttackRight", false);
			break;
		case yh::enums::Directions::End:
			break;
		default:
			break;
		}

		for (int i = 0; i < 2; i++)
		{
			Vector2 fire_pos = tr->GetPosition();
			ArrowProjectile* ap = object::Instantiate<ArrowProjectile>(eLayerType::Monster, Vector2(fire_pos.x,fire_pos.y - (10.0f * i)));
			ap->SetDirection(direct);
		}

		switch (direct)
		{
		case yh::enums::Directions::Forward:
			direct = Directions::Right;
			break;
		case yh::enums::Directions::Backward:
			direct = Directions::Left;
			break;
		case yh::enums::Directions::Left:
			direct = Directions::Forward;
			break;
		case yh::enums::Directions::Right:
			direct = Directions::Backward;
			break;
		case yh::enums::Directions::End:
			break;
		default:
			break;
		}

		state = MonsterState::Idle;

	}
	void BlueKnight::Death()
	{

	}
	void BlueKnight::Freeze()
	{
		freeze_time -= Time::DeltaTime();
		if (freeze_time <= 0.0f)
		{
			freeze_time = 1.5f;
			state = MonsterState::Idle;
		}
	}
}