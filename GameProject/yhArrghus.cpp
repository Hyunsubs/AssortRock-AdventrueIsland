#include "yhArrghus.h"
#include "yhAnimator.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhObject.h"
#include "yhArrghusPiece.h"
#include "yhTime.h"
#include "yhMonsterTemplate.h"
#include "yhPlayer.h"
#include "yhCollider.h"

namespace yh
{
	Arrghus::Arrghus() :
		  anim(nullptr)
		, tr(nullptr)
		, attack_time(3.0f)
		, moving_time(0.5f)
		, cur_phase(Phase::First)
		, first_phase(FirstPhase::Idle)
		, second_phase(SecondPhase::None)
		, col(nullptr)
		, idle_time(4.0f)
		, moving_count(3)
		, degree(0.0f)
		, pieces({})
		, piece_pos_arr()
	{
		wstring boss_path = BOSS_PATH;
		
		piece_pos_arr[0] = Vector2(20.0f, 30.0f);
		piece_pos_arr[1] = Vector2(-20.0f, -30.0f);
		piece_pos_arr[2] = Vector2(10.0f, 10.0f);
		piece_pos_arr[3] = Vector2(-10.0f, 30.0f);
		piece_pos_arr[4] = Vector2(-20.0f, -30.0f);
		piece_pos_arr[5] = Vector2(-20.0f, 30.0f);
		piece_pos_arr[6] = Vector2(-30.0f, 25.0f);
		piece_pos_arr[7] = Vector2(35.0f, 20.0f);
		piece_pos_arr[8] = Vector2(-45.0f, 30.0f);
		piece_pos_arr[9] = Vector2(30.0f, -40.0f);
		piece_pos_arr[10] = Vector2(-40.0f, 10.0f);
		piece_pos_arr[11] = Vector2(35.0f, -20.0f);
		piece_pos_arr[12] = Vector2(-35.0f, -35.0f);
		piece_pos_arr[13] = Vector2(-15.0f, -15.0f);
		piece_pos_arr[14] = Vector2(15.0f, 15.0f);

		anim = AddComponent<Animator>();
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();
		col->SetSize(Vector2(50.0f, 40.0f));
		col->SetOffset(Vector2(0.0f, -20.0f));
		anim->CreateAnimationFolder(L"FirstPhaseMoving", boss_path + L"Arrghus\\FirstPhase\\Body",Vector2::Zero,0.5f);
		anim->CreateAnimationFolder(L"SecondPhaseMoving", boss_path + L"Arrghus\\SecondPhase\\body", Vector2::Zero, 0.5f);
		anim->SetScale(Vector2::Double);
		SetHp(5);

		anim->PlayAnimation(L"FirstPhaseMoving", true);

		for (int i = 0; i < 15; i++)
		{
			ArrghusPiece* piece = object::Instantiate<ArrghusPiece>(eLayerType::Effect,tr->GetPosition() + piece_pos_arr[i]);
			pieces.push_back(piece);
		}
	}

	Arrghus::~Arrghus()
	{
	}

	void Arrghus::Initialize()
	{

	}

	void Arrghus::Update()
	{
		MonsterTemplate::Update();
		
		switch (cur_phase)
		{
		case yh::Phase::First:
			switch (first_phase)
			{
			case yh::FirstPhase::Idle:
				IdleFirst();
				break;
			case yh::FirstPhase::Moving:
				MovingFirst();
				break;
			case yh::FirstPhase::Attack:
				AttackFirst();
				break;
			case yh::FirstPhase::None:
				break;
			default:
				break;
			}
			break;
		case yh::Phase::Second:
			switch (second_phase)
			{
			case yh::SecondPhase::Moving:
				MovingSecond();
				break;
			case yh::SecondPhase::Jumping:
				JumpingSecond();
				break;
			case yh::SecondPhase::Smashing:
				SmashingSecond();
				break;
			case yh::SecondPhase::None:
				break;
			default:
				break;
			}
		default:
			break;
		}
	}

	void Arrghus::Render(HDC hdc)
	{
		MonsterTemplate::Render(hdc);
	}

	void Arrghus::OnCollisionEnter(Collider* other)
	{
	
	}

	void Arrghus::OnCollisionStay(Collider* other)
	{
	}

	void Arrghus::OnCollisionExit(Collider* other)
	{
	}


	void Arrghus::IdleFirst()
	{
		idle_time -= Time::DeltaTime();
		if (idle_time <= 0.0f)
		{
			idle_time = 4.0f;
			first_phase = FirstPhase::Moving;
		}
		/*if (moving_count <= 0)
		{
			moving_count = 3;
			first_phase = FirstPhase::Attack;
		}*/

		for (int i = 0; i < 15; i++)
		{
			int rand_x = rand() % 150 * Time::DeltaTime();
			int rand_y = rand() % 150 * Time::DeltaTime();
			Vector2 changed_position = tr->GetPosition() + piece_pos_arr[i];
			Transform* piece_tr = pieces[i]->GetComponent<Transform>();
			piece_tr->SetPosition(Vector2(changed_position.x + rand_x, changed_position.y + rand_y));

		}
	}

	void Arrghus::MovingFirst()
	{
		Vector2 cur_pos = tr->GetPosition();

		degree += Time::DeltaTime();
		if (degree >= 360.0f)
			degree = 0.0f;

		if (cur_pos.x - player_pos.x < 0.0f)
			cur_pos.x += 150.0f * Time::DeltaTime();
		else
			cur_pos.x -= 150.0f * Time::DeltaTime();

		if (cur_pos.y - player_pos.y < 0.0f)
			cur_pos.y += 150.0f * Time::DeltaTime();
		else
			cur_pos.y -= 150.0f * Time::DeltaTime();

		tr->SetPosition(cur_pos);

		for (int i = 0; i < 15; i++)
		{
			Vector2 changed_position = tr->GetPosition() + piece_pos_arr[i];
			Transform* piece_tr = pieces[i]->GetComponent<Transform>();
			piece_tr->SetPosition(changed_position);
	
		}

		moving_time -= Time::DeltaTime();
		if (moving_time <= 0.0f)
		{
			moving_time = 0.5f;
			first_phase = FirstPhase::Idle;
			moving_count--;
		}

		

	}


	void Arrghus::AttackFirst()
	{
	}


	void Arrghus::MovingSecond()
	{
	}
	void Arrghus::JumpingSecond()
	{
	}
	void Arrghus::SmashingSecond()
	{
	}
}