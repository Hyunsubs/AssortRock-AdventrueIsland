#include "yhArrghusPiece.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhObject.h"
#include "yhTime.h"
#include "yhClutchParts.h"
#include "yhCollider.h"
#include "yhPlayer.h"

namespace yh
{
	ArrghusPiece::ArrghusPiece() :
		  anim(nullptr)
		, tr(nullptr)
		, is_seperated(false)
		, state(PieceState::Idle)
		, direct(Directions::End)
		, idle_time(2.0f)
		, move_time(0.5f)
		, attack_time(8.0f)
		, move_count(3)
		, degree(0.0f)
	{
		wstring boss_path = BOSS_PATH;
		tr = GetComponent<Transform>();
		anim = AddComponent<Animator>();
		col = AddComponent<Collider>();

		anim->CreateAnimationFolder(L"PieceIdle", boss_path + L"Arrghus\\FirstPhase\\Pieces", Vector2::Zero, 0.2f);
		anim->CreateAnimationFolder(L"CaughtPiece", boss_path + L"Arrghus\\FirstPhase\\Caught_Pieces", Vector2::Zero, 0.2f);
		anim->CreateAnimationFolder(L"PieceDead", boss_path + L"Arrghus\\FirstPhase\\Piece_Dead", Vector2::Zero, 0.1f);
		anim->SetScale(Vector2::Double);

		anim->PlayAnimation(L"PieceIdle", true);

		col->SetSize(Vector2(20.0f, 20.0f));

		SetHp(3);
	}
	ArrghusPiece::~ArrghusPiece()
	{
	}
	void ArrghusPiece::Initialize()
	{
	}
	void ArrghusPiece::Update()
	{
		MonsterTemplate::Update();

		if (GetHp() <= 0 && state != PieceState::Dead)
		{
			anim->PlayAnimation(L"PieceDead", false);
			state = PieceState::Dead;
		}

		switch (state)
		{
		case yh::PieceState::Idle:
			Idle();
			break;
		case yh::PieceState::Move:
			Move();
			break;
		case yh::PieceState::Attack:
			Attack();
			break;
		case yh::PieceState::Grapped:
			Grapped();
			break;

		case yh::PieceState::Dead:
			Dead();
			break;
		default:
			break;
		}
	}
	void ArrghusPiece::Render(HDC hdc)
	{
		MonsterTemplate::Render(hdc);

	}
	void ArrghusPiece::OnCollisionEnter(Collider* other)
	{
		if (other == nullptr)
			return;
		if (state == PieceState::Dead)
			return;
		ClutchParts* clutch = dynamic_cast<ClutchParts*>(other->GetOwner());
		if (clutch != nullptr && clutch->GetClutchType() == ClutchTypes::End)
		{
			state = PieceState::Grapped;
			anim->PlayAnimation(L"CaughtPiece", true);
		}

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr && state != PieceState::Dead && !(player->GetIsHit()))
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
	void ArrghusPiece::OnCollisionStay(Collider* other)
	{
		ClutchParts* clutch = dynamic_cast<ClutchParts*>(other->GetOwner());
		if (clutch != nullptr && clutch->GetClutchType() == ClutchTypes::End)
		{
			state = PieceState::Grapped;
			anim->PlayAnimation(L"CaughtPiece", true);
		}
	}
	void ArrghusPiece::OnCollisionExit(Collider* other)
	{
	}
	void ArrghusPiece::Idle()
	{
		
	}
	void ArrghusPiece::Move()
	{
	
	}
	void ArrghusPiece::Attack()
	{
		
	}

	void ArrghusPiece::Grapped()
	{
		
	}

	void ArrghusPiece::Dead()
	{
		if (anim->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}