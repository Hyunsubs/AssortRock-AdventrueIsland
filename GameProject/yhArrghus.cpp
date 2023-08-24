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
#include "yhPlayerSword.h"
#include "yhArrghusShadow.h"
#include "yhHeartContainer.h"

namespace yh
{
	Arrghus::Arrghus() :
		  anim(nullptr)
		, tr(nullptr)
		, attack_time(3.0f)
		, moving_time(0.5f)
		, cur_phase(Phase::First)
		, first_phase(ArrghusFirstPhase::Idle)
		, second_phase(ArrghusSecondPhase::None)
		, col(nullptr)
		, idle_time(0.5f)
		, moving_count(3)
		, degree(0.0f)
		, pieces({})
		, piece_pos_arr()
		, is_changed(false)
		, spin_power(0.0f)
		, second_moving_time(4.0f)
		, second_jumping_time(2.0f)
		, second_smashing_time(1.0f)
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
		anim->CreateAnimationFolder(L"SecondPhaseMoving", boss_path + L"Arrghus\\SecondPhase\\body", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"SecondPhaseShadow", boss_path + L"Arrghus\\SecondPhase\\body", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"SecondPhaseSmashing", boss_path + L"Arrghus\\SecondPhase\\body", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"ArrghusDeadAnim", boss_path + L"Arrghus\\Dead",Vector2::Zero,0.3f);
		anim->SetScale(Vector2::Double);
		SetHp(10);

		anim->PlayAnimation(L"FirstPhaseMoving", true);
		

		for (int i = 0; i < PIECE_AMOUNT; i++)
		{
			ArrghusPiece* piece = object::Instantiate<ArrghusPiece>(eLayerType::Boss,tr->GetPosition() + piece_pos_arr[i]);
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
		GameObject::Update();

		int hp = GetHp();
		if (hp <= 0 && second_phase != ArrghusSecondPhase::Dead)
		{
			anim->PlayAnimation(L"ArrghusDeadAnim",false);
			second_phase = ArrghusSecondPhase::Dead;
		}

		for (int i = 0; i < PIECE_AMOUNT; i++)
		{
			if (pieces[i]->GetPieceState() == PieceState::Dead)
			{
				is_changed = true;
			}
			else
			{
				is_changed = false;
				break;
			}
		}

		if (is_changed && cur_phase == Phase::First)
		{
			anim->PlayAnimation(L"SecondPhaseMoving",true);
			cur_phase = Phase::Second;
			direct = Directions::DownRight;
			second_phase = ArrghusSecondPhase::Moving;
		}


		switch (cur_phase)
		{
		case yh::Phase::First:
			switch (first_phase)
			{
			case yh::ArrghusFirstPhase::Idle:
				IdleFirst();
				break;
			case yh::ArrghusFirstPhase::Moving:
				MovingFirst();
				break;
			case yh::ArrghusFirstPhase::Attack:
				AttackFirst();
				break;
			case yh::ArrghusFirstPhase::AttackBack:
				AttackBackFirst();
				break;
			case yh::ArrghusFirstPhase::None:
				break;
			default:
				break;
			}
			break;
		case yh::Phase::Second:
			switch (second_phase)
			{
			case yh::ArrghusSecondPhase::Moving:
				MovingSecond();
				break;
			case yh::ArrghusSecondPhase::Jumping:
				JumpingSecond();
				break;
			case yh::ArrghusSecondPhase::Smashing:
				SmashingSecond(attack_pos);
				break;
			case yh::ArrghusSecondPhase::Dead:
				Dead();
				break;
			case yh::ArrghusSecondPhase::None:
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
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (cur_phase != Phase::First && player != nullptr && second_phase != ArrghusSecondPhase::Dead && !(player->GetIsHit()) && player->GetState() != Player::PlayerState::Death)
		{
			Transform* tr = player->GetComponent<Transform>();
			int player_hp = player->GetHp();
			if (player_hp <= 0)
				return;
			player_hp--;
			player->SetHp(player_hp);
			player->SetState(Player::PlayerState::Hit);
			Animator* player_anim = player->GetComponent<Animator>();
			switch (player->GetDirection())
			{
			case Directions::Forward:
				player_anim->PlayAnimation(L"LinkHitForward", false);
				break;
			case Directions::Backward:
				player_anim->PlayAnimation(L"LinkHitBackward", false);
				break;
			case Directions::Left:
				player_anim->PlayAnimation(L"LinkHitLeft", false);
				break;
			case Directions::Right:
				player_anim->PlayAnimation(L"LinkHitRight", false);
				break;
			default:
				break;
			}

		}
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
			idle_time = 0.5f;
			first_phase = ArrghusFirstPhase::Moving;
		}
		if (moving_count <= 0)
		{
			moving_count = 3;
			first_phase = ArrghusFirstPhase::Attack;
		}

		for (int i = 0; i < PIECE_AMOUNT; i++)
		{
			if (pieces[i]->GetPieceState() != PieceState::Grapped && pieces[i]->GetPieceState() != PieceState::Dead)
			{
				int rand_x = rand() % 200 * Time::DeltaTime();
				int rand_y = rand() % 200 * Time::DeltaTime();
				Vector2 changed_position = tr->GetPosition() + piece_pos_arr[i];
				Transform* piece_tr = pieces[i]->GetComponent<Transform>();
				piece_tr->SetPosition(Vector2(changed_position.x + rand_x, changed_position.y + rand_y));
			}
		}


	}

	void Arrghus::MovingFirst()
	{
		Vector2 cur_pos = tr->GetPosition();


		if (cur_pos.x - player_pos.x < 0.0f)
			cur_pos.x += 100.0f * Time::DeltaTime();
		else
			cur_pos.x -= 100.0f * Time::DeltaTime();

		if (cur_pos.y - player_pos.y < 0.0f)
			cur_pos.y += 100.0f * Time::DeltaTime();
		else
			cur_pos.y -= 100.0f * Time::DeltaTime();

		tr->SetPosition(cur_pos);
		
		
		for (int i = 0; i < PIECE_AMOUNT; i++)
		{
			if (pieces[i]->GetPieceState() != PieceState::Grapped && pieces[i]->GetPieceState() != PieceState::Dead)
			{
				Vector2 changed_position = tr->GetPosition() + piece_pos_arr[i];
				Transform* piece_tr = pieces[i]->GetComponent<Transform>();
				piece_tr->SetPosition(changed_position);
			}
		}

		moving_time -= Time::DeltaTime();
		if (moving_time <= 0.0f)
		{
			moving_time = 0.5f;
			first_phase = ArrghusFirstPhase::Idle;
			moving_count--;
		}

		

	}


	void Arrghus::AttackFirst()
	{
		
		attack_time -= Time::DeltaTime();
		degree += 30.0f * Time::DeltaTime();
		spin_power += Time::DeltaTime();

		if (attack_time <= 0.0f)
		{
			attack_time = 3.0f;
			first_phase = ArrghusFirstPhase::AttackBack;
		}
		
		for (int i = 0; i < PIECE_AMOUNT; i++)
		{
			if (pieces[i]->GetPieceState() != PieceState::Grapped && pieces[i]->GetPieceState() != PieceState::Dead)
			{
				Transform* piece_tr = pieces[i]->GetComponent<Transform>();
				Vector2 Rotate_pos = Rotate(tr->GetPosition(), degree * i);
				piece_tr->SetPosition(tr->GetPosition() + Rotate_pos * (70.0f + spin_power * 20.0f));
			}
		}

	}

	void Arrghus::AttackBackFirst()
	{
		attack_time -= Time::DeltaTime();
		degree += 30.0f * Time::DeltaTime();
		spin_power -= Time::DeltaTime();

		if (attack_time <= 0.0f)
		{
			attack_time = 3.0f;
			spin_power = 0.0f;
			first_phase = ArrghusFirstPhase::Idle;
		}

		for (int i = 0; i < PIECE_AMOUNT; i++)
		{
			if (pieces[i]->GetPieceState() != PieceState::Grapped && pieces[i]->GetPieceState() != PieceState::Dead)
			{
				Transform* piece_tr = pieces[i]->GetComponent<Transform>();
				Vector2 Rotate_pos = Rotate(tr->GetPosition(), degree * i);
				piece_tr->SetPosition(tr->GetPosition() - Rotate_pos * (70.0f + spin_power * 20.0f));
			}
		}
	}


	void Arrghus::MovingSecond()
	{
		CheckPixel(MonsterTemplate::PixelTexture ,MonsterTemplate::map_size);
		second_moving_time -= Time::DeltaTime();

		if (second_moving_time <= 0.0f)
		{
			second_moving_time = 4.0f;
			jump_pos = tr->GetPosition();
			arrghus_shadow = object::Instantiate<ArrghusShadow>(eLayerType::Effect, jump_pos);
			second_phase = ArrghusSecondPhase::Jumping;
		}

		Vector2 cur_pos = tr->GetPosition();
		switch (direct)
		{
		case yh::enums::Directions::UpRight:
			cur_pos.x += 200.0f * Time::DeltaTime();
			cur_pos.y -= 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::UpLeft:
			cur_pos.x -= 200.0f * Time::DeltaTime();
			cur_pos.y -= 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::DownRight:
			cur_pos.x += 200.0f * Time::DeltaTime();
			cur_pos.y += 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::DownLeft:
			cur_pos.x -= 200.0f * Time::DeltaTime();
			cur_pos.y += 200.0f * Time::DeltaTime();
			break;
		default:
			break;
		}
		tr->SetPosition(cur_pos);

	}
	void Arrghus::JumpingSecond()
	{
		anim->PlayAnimation(L"SecondPhaseSmashing", true);
		Vector2 cur_pos = tr->GetPosition();
		if (cur_pos.y >= -500.0f)
		{
			cur_pos.y -= 800.0f * Time::DeltaTime();
			tr->SetPosition(cur_pos);
		}

		if (cur_pos.y <= -500.0f)
		{
			second_jumping_time -= Time::DeltaTime();
			Transform* shadow_tr = arrghus_shadow->GetComponent<Transform>();
			Vector2 shadow_pos = shadow_tr->GetPosition();
			if (shadow_pos.x - player_pos.x < 0.0f)
				shadow_pos.x += 100.0f * Time::DeltaTime();
			else
				shadow_pos.x -= 100.0f * Time::DeltaTime();

			if (shadow_pos.y - player_pos.y < 0.0f)
				shadow_pos.y += 100.0f * Time::DeltaTime();
			else
				shadow_pos.y -= 100.0f * Time::DeltaTime();
			shadow_tr->SetPosition(shadow_pos);
		}
	
		if (second_jumping_time <= 0.0f)
		{
			Transform* shadow_tr = arrghus_shadow->GetComponent<Transform>();
			Vector2 shadow_pos = shadow_tr->GetPosition();
			second_jumping_time = 2.0f;
			tr->SetPosition(Vector2(shadow_pos.x, tr->GetPosition().y));
			Destroy(arrghus_shadow);
			second_phase = ArrghusSecondPhase::Smashing;
		}
	}

	void Arrghus::SmashingSecond(Vector2 attack_pos)
	{
		Transform* shadow_tr = arrghus_shadow->GetComponent<Transform>();
		Vector2 shadow_pos = shadow_tr->GetPosition();
		Vector2 cur_pos = tr->GetPosition();
		if (cur_pos.y <= shadow_pos.y)
		{
			cur_pos.y += 800.0f * Time::DeltaTime();
		}

		tr->SetPosition(cur_pos);

		if (cur_pos.y >= shadow_pos.y)
		{
			anim->PlayAnimation(L"SecondPhaseMoving", true);
			second_phase = ArrghusSecondPhase::Moving;
		}
	}

	void Arrghus::Dead()
	{
		if (anim->IsActiveAnimationComplete())
		{
			object::Instantiate<HeartContainer>(eLayerType::Items, tr->GetPosition());
			Destroy(this);
		}
	}

	void Arrghus::CheckPixel(Texture* pixel_texture, Vector2 map_size)
	{
		if (pixel_texture == nullptr)
			return;
		std::vector<COLORREF> rgbs;
		Transform* my_tr = GetComponent<Transform>();
		COLORREF down_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x, my_tr->GetPosition().y + map_size.y + 20);
		COLORREF up_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x, my_tr->GetPosition().y + map_size.y - 20);
		COLORREF left_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x - 20, my_tr->GetPosition().y + map_size.y);
		COLORREF right_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x + 20, my_tr->GetPosition().y + map_size.y);

		rgbs.push_back(down_color);
		rgbs.push_back(up_color);
		rgbs.push_back(left_color);
		rgbs.push_back(right_color);

		for (int i = 0; i < 4; ++i)
		{
			if (rgbs[i] == RGB(0, 0, 255))
			{
				switch (direct)
				{
				case yh::enums::Directions::UpRight:
					direct = Directions::DownRight;
					break;
				case yh::enums::Directions::UpLeft:
					direct = Directions::UpRight;
					break;
				case yh::enums::Directions::DownRight:
					direct = Directions::DownLeft;
					break;
				case yh::enums::Directions::DownLeft:
					direct = Directions::UpLeft;
					break;
				case yh::enums::Directions::End:
					break;
				default:
					break;
				}
			}

		}
	}



}