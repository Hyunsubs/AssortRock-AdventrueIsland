#include "yhGanon.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhCollider.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhAsciiRender.h"
#include "yhObject.h"
#include "yhCamera.h"
#include "yhInput.h"
#include <time.h>
#include "yhGanonTrident.h"
#include "yhTime.h"
#include "yhPlayer.h"
#include "yhGanonFireBats.h"

namespace yh
{
	Ganon::Ganon() :
		  tr(nullptr)
		, anim(nullptr)
		, col(nullptr)
		, first_phase(FirstPhase::None)
		, second_phase(SecondPhase::None)
		, third_phase(ThirdPhase::None)
		, cur_phase(CurrentPhase::FirstTalking)
		, direct(Directions::Backward)
		, idx(0)
		, cur_alpha(1.0f)
		, rand_num(0)
		, first_hp(20)
		, second_hp(20)
		, third_hp(20)
		, second_on(false)
		, third_on(false)
		, player(nullptr)
		, make_bats(0.0f)
		, max_bats(0)
	{
		wstring boss_path = BOSS_PATH;

		tr = GetComponent<Transform>();
		anim = AddComponent<Animator>();
		col = AddComponent<Collider>();

		anim->SetScale(Vector2::Double);
		anim->CreateAnimationFolder(L"GanonJumpingAnim", boss_path + L"Ganon\\Jumping",Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"GanonTridentSeperatedForward", boss_path + L"Ganon\\GanonTridentSeperated\\Forward",Vector2::Zero,0.3f);
		anim->CreateAnimationFolder(L"GanonTridentSeperatedBackward", boss_path + L"Ganon\\GanonTridentSeperated\\Backward", Vector2::Zero,0.3f);
		anim->CreateAnimationFolder(L"GanonPhantomMoveForward", boss_path + L"Ganon\\PhantomMove\\Forward");
		anim->CreateAnimationFolder(L"GanonPhantomMoveBackward", boss_path + L"Ganon\\PhantomMove\\Backward");
		anim->CreateAnimationFolder(L"GanonPreparing", boss_path + L"Ganon\\Preparing");
		anim->CreateAnimationFolder(L"GanonSpearSpinningForward", boss_path + L"Ganon\\SpearSpinning\\Forward");
		anim->CreateAnimationFolder(L"GanonSpearSpinningBackward", boss_path + L"Ganon\\SpearSpinning\\Backward");
		anim->CreateAnimationFolder(L"GanonDeadAnim", boss_path + L"Arrghus\\Dead", Vector2::Zero, 0.3f);

		anim->PlayAnimation(L"GanonPreparing", false);
		col->SetSize(Vector2(60.0f, 70.0f));


		//가논 랜덤위치
		FirstPhasePos[0] = Vector2(-155.0f, 60.0f);
		FirstPhasePos[1] = Vector2(-266.0f, -59.0f);
		FirstPhasePos[2] = Vector2(45.0f, -64.0f);
		FirstPhasePos[3] = Vector2(219.0f, 100.0f);
		FirstPhasePos[4] = Vector2(320.0f, -78.0f);
		
		srand((unsigned)time(NULL));
	}

	Ganon::~Ganon()
	{
	}

	void Ganon::Initialize()
	{
		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));
		ascii->SetString("I NEVER IMAGINED A BOY\nLIKE YOU COULD GIVE\nME SO MUCH TROUBLE");
		ascii->Destroy();
		first_dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));
		ascii->SetString("UNBIELIEVABLE THAT YOU\nDEFEATED MY ARRGHUS\nBUT I WILL NEVER LOSE");
		ascii->Destroy();
		first_dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));
		ascii->SetString("COME ON BOY\nLETS END THIS GAME");
		ascii->Destroy();
		first_dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));
		ascii->SetString("YOU ARE DOING WELL LAD\nBUT CAN YOU BREAK\nTHROUGH THIS");
		ascii->Destroy();
		second_dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));
		ascii->SetString("EN GARDE");
		ascii->Destroy();
		second_dialogue.push_back(ascii);
	}

	void Ganon::Update()
	{
		GameObject::Update();

		if (first_hp <= 0 && !second_on)
		{
			cur_phase = CurrentPhase::SecondTalking;
			second_on = true;
		}
		if (second_hp <= 0 && !third_on)
		{
			cur_phase = CurrentPhase::Third;
			third_phase = ThirdPhase::Death;
			anim->PlayAnimation(L"GanonDeadAnim", false);
			third_on = true;
		}

		switch (cur_phase)
		{
		case CurrentPhase::First:
			switch (first_phase)
			{
			case FirstPhase::Throwing:
				ThrowingFirst();
				break;
			case FirstPhase::PhantomMove:
				PhantomMoveFirst(rand_num);
				break;
			case FirstPhase::Spinning:
				SpinningFirst();
				break;
			case FirstPhase::None:
				break;
			default:
				break;
			}
			break;
		case CurrentPhase::Second:
			switch (second_phase)
			{
			case SecondPhase::PhantomMove:
				PhantomMoveSecond(rand_num);
				break;
			case SecondPhase::FireSpin:
				FireSpinSecond();
				break;
			case SecondPhase::BatsFollowing:
				BatsFollowingSecond();
				break;
			case SecondPhase::None:
				break;
			default:
				break;
			}
			break;
		case CurrentPhase::Third:
			switch (third_phase)
			{
			case ThirdPhase::Death:
				Death();
			case ThirdPhase::None:
				break;
			default:
				break;
			}
			break;
		case CurrentPhase::FirstTalking:
			FirstTalking();
			break;
		case CurrentPhase::SecondTalking:
			SecondTalking();
			break;
		default:
			break;
		}

	}

	void Ganon::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Ganon::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr && !(player->GetIsHit()))
		{
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
	void Ganon::OnCollisionStay(Collider* other)
	{
	}
	void Ganon::OnCollisionExit(Collider* other)
	{
	}
	void Ganon::ThrowingFirst()
	{	
		switch (direct)
		{
		case Directions::Forward:
			anim->PlayAnimation(L"GanonTridentSeperatedForward", false);
			break;
		case Directions::Backward:
			anim->PlayAnimation(L"GanonTridentSeperatedBackward", false);
			break;
		default:
			break;
		}
		trident = object::Instantiate<GanonTrident>(eLayerType::Boss,tr->GetPosition());
		trident->SetPlayerPos(PlayerPos);

		rand_num = rand() % 5;
		if (rand_num == 0 || rand_num == 3)
			direct = Directions::Forward;
		else
			direct = Directions::Backward;
		first_phase = FirstPhase::PhantomMove;
	}
	void Ganon::PhantomMoveFirst(int rand_num)
	{
		Vector2 cur_pos = tr->GetPosition();
		Vector2 move_pos = FirstPhasePos[rand_num];


		if (anim->IsActiveAnimationComplete())
		{
			switch (direct)
			{
			case yh::enums::Directions::Forward:
				anim->PlayAnimation(L"GanonPhantomMoveForward", false);
				break;
			case yh::enums::Directions::Backward:
				anim->PlayAnimation(L"GanonPhantomMoveBackward", false);
				break;
			default:
				break;
			}
		}


		cur_alpha -= Time::DeltaTime();
		if (cur_alpha >= 1.0f)
			cur_alpha = 1.0f;
		if (cur_alpha <= 0.0f)
			cur_alpha = 0.0f;
		anim->SetAlpha(cur_alpha);


		if (cur_alpha == 0.0f)
		{
			tr->SetPosition(move_pos);
			cur_alpha = 1.0f;
			anim->SetAlpha(cur_alpha);
			switch (direct)
			{
			case yh::enums::Directions::Forward:
				anim->PlayAnimation(L"GanonSpearSpinningForward", false);
				break;
			case yh::enums::Directions::Backward:
				anim->PlayAnimation(L"GanonSpearSpinningBackward", false);
				break;
			default:
				break;
			}
			first_phase = FirstPhase::Spinning;
		}

		
	}
	void Ganon::SpinningFirst()
	{
		if (anim->IsActiveAnimationComplete())
		{
			first_phase = FirstPhase::Throwing;
		}
		
	}
	void Ganon::FirstTalking()
	{
		Transform* text_tr = first_dialogue[idx]->GetComponent<Transform>();
		text_tr->SetPosition(Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));

		if (first_dialogue[idx]->GetState() != eState::Active)
		{
			first_dialogue[idx]->Activate();
			first_dialogue[idx]->PrintAsciis();
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			first_dialogue[idx]->Destroy();
			idx++;
			if (idx >= 3)
			{
				idx = 0;
				player->SetState(Player::PlayerState::Idle);
				cur_phase = CurrentPhase::First;
				first_phase = FirstPhase::Throwing;
			}
		}
	}

	void Ganon::SecondTalking()
	{
		Transform* text_tr = second_dialogue[idx]->GetComponent<Transform>();
		text_tr->SetPosition(Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));

		if (second_dialogue[idx]->GetState() != eState::Active)
		{
			second_dialogue[idx]->Activate();
			second_dialogue[idx]->PrintAsciis();
		}
		if (Input::GetKeyDown(eKeyCode::I))
		{
			second_dialogue[idx]->Destroy();
			idx++;
			if (idx >= 2)
			{
				idx = 0;
				player->SetState(Player::PlayerState::Idle);
				switch (direct)
				{
				case yh::enums::Directions::Forward:
					anim->PlayAnimation(L"GanonSpearSpinningForward", true);
					break;
				case yh::enums::Directions::Backward:
					anim->PlayAnimation(L"GanonSpearSpinningBackward", true);
					break;
				default:
					break;
				}
				cur_phase = CurrentPhase::Second;
				second_phase = SecondPhase::FireSpin;
			}
		}
	}

	void Ganon::PhantomMoveSecond(int rand_num)
	{
		Vector2 cur_pos = tr->GetPosition();
		Vector2 move_pos = FirstPhasePos[rand_num];


		cur_alpha -= Time::DeltaTime();
		if (cur_alpha >= 1.0f)
			cur_alpha = 1.0f;
		if (cur_alpha <= 0.0f)
			cur_alpha = 0.0f;
		anim->SetAlpha(cur_alpha);


		if (cur_alpha == 0.0f)
		{
			tr->SetPosition(move_pos);
			cur_alpha = 1.0f;
			anim->SetAlpha(cur_alpha);
			switch (direct)
			{
			case yh::enums::Directions::Forward:
				anim->PlayAnimation(L"GanonSpearSpinningForward", true);
				break;
			case yh::enums::Directions::Backward:
				anim->PlayAnimation(L"GanonSpearSpinningBackward", true);
				break;
			default:
				break;
			}
			second_phase = SecondPhase::FireSpin;
		}
	}


	void Ganon::FireSpinSecond()
	{
	
		make_bats += Time::DeltaTime();
		if (make_bats >= 0.5f)
		{
			make_bats = 0.0f;
			max_bats++;
			GanonFireBats* bat = object::Instantiate<GanonFireBats>(eLayerType::Monster, tr->GetPosition());
			bat->SetPlayerPos(PlayerPos);
			bat->SetBossPos(tr->GetPosition());
		}

		if (max_bats >= 8)
		{
			max_bats = 0;
			second_phase = SecondPhase::PhantomMove;
			rand_num = rand() % 5;
			if (rand_num == 0 || rand_num == 3)
				direct = Directions::Forward;
			else
				direct = Directions::Backward;

			switch (direct)
			{
			case yh::enums::Directions::Forward:
				anim->PlayAnimation(L"GanonPhantomMoveForward", false);
				break;
			case yh::enums::Directions::Backward:
				anim->PlayAnimation(L"GanonPhantomMoveBackward", false);
				break;
			default:
				break;
			}

		}
			

	}
	void Ganon::BatsFollowingSecond()
	{
	}
	void Ganon::Death()
	{
		if (anim->IsActiveAnimationComplete())
		{
			Destroy(this);
			
		}
	}
}