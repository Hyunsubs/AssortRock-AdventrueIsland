#include "yhGanonTrident.h"
#include "yhAnimator.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhPlayer.h"
#include "yhTime.h"

namespace yh
{
	GanonTrident::GanonTrident() :
		  tr(nullptr)
		, anim(nullptr)
		, col(nullptr)
		, exist_time(0.5f)
	{
		wstring boss_path = BOSS_PATH;
		tr = GetComponent<Transform>();
		anim = AddComponent<Animator>();
		col = AddComponent<Collider>();

		anim->CreateAnimationFolder(L"TridentSpinAnim",boss_path + L"Ganon\\Trident");
		anim->SetScale(Vector2::Double);
		anim->PlayAnimation(L"TridentSpinAnim",true);

		col->SetSize(Vector2(20.0f, 70.0f));

	}
	GanonTrident::~GanonTrident()
	{
	}
	void GanonTrident::Initialize()
	{
	}
	void GanonTrident::Update()
	{
		GameObject::Update();
		exist_time -= Time::DeltaTime();
		Vector2 cur_pos = tr->GetPosition();
		if (exist_time <= 0.0f)
		{
			Destroy(this);
		}

		

		if (cur_pos.x <= Player_Pos.x)
			cur_pos.x += 500.0f * Time::DeltaTime();
		else
			cur_pos.x -= 500.0f * Time::DeltaTime();
		if (cur_pos.y <= Player_Pos.y)
			cur_pos.y += 500.0f * Time::DeltaTime();
		else
			cur_pos.y -= 500.0f * Time::DeltaTime();

		tr->SetPosition(cur_pos);
	}
	void GanonTrident::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GanonTrident::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr && !(player->GetIsHit()) && GetState() != eState::Dead)
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
	void GanonTrident::OnCollisionStay(Collider* other)
	{
	}
	void GanonTrident::OnCollisionExit(Collider* other)
	{
	}
}