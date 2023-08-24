#include "yhGanonFireBats.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhTime.h"
#include "yhCollider.h"
#include "yhPlayer.h"

namespace yh
{
	GanonFireBats::GanonFireBats() :
		  tr(nullptr)
		, anim(nullptr)
		, degree(0.0f)
		, col(nullptr)
		, state(BatsState::Moving)
		, following_time(1.5f)
	{
		type = rand() % 8;
		wstring boss_path = BOSS_PATH;
		tr = GetComponent<Transform>();
		anim = AddComponent<Animator>();
		col = AddComponent<Collider>();

		col->SetSize(Vector2(20.0f, 20.0f));

		anim->CreateAnimationFolder(L"BeforeFlying", boss_path + L"Ganon\\FireBats\\BeforeFlying",Vector2::Zero,0.2f);
		anim->CreateAnimationFolder(L"AfterFlying", boss_path + L"Ganon\\FireBats\\AfterFlying",Vector2::Zero,0.1f);

		anim->PlayAnimation(L"BeforeFlying", true);
	}
	GanonFireBats::~GanonFireBats()
	{
	}
	void GanonFireBats::Initialize()
	{
	}
	void GanonFireBats::Update()
	{
		GameObject Update();

		switch (state)
		{
		case yh::BatsState::Moving:
			Moving(boss_pos);
			break;
		case yh::BatsState::Following:
			Following();
			break;
		case yh::BatsState::Dead:
			break;
		default:
			break;
		}
	}
	void GanonFireBats::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GanonFireBats::OnCollisionEnter(Collider* other)
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
	void GanonFireBats::OnCollisionStay(Collider* other)
	{
	}
	void GanonFireBats::OnCollisionExit(Collider* other)
	{
	}
	void GanonFireBats::Moving(Vector2 pos)
	{
		degree += 120.0f * Time::DeltaTime();
		Vector2 Rotate_Pos = Rotate(tr->GetPosition(), degree);
		tr->SetPosition(pos + (Rotate_Pos * 50.0f));

		if (degree >= 480.0f)
		{
			state = BatsState::Following;
			anim->PlayAnimation(L"AfterFlying", true);
		}
	}

	void GanonFireBats::Following()
	{
		Vector2 cur_pos = tr->GetPosition();
		switch (type)
		{
		case 0:
			break;
			cur_pos.x -= 400.0f * Time::DeltaTime();
			cur_pos.y -= 400.0f * Time::DeltaTime();
		case 1:
			cur_pos.x -= 400.0f * Time::DeltaTime();
			cur_pos.y += 400.0f * Time::DeltaTime();
			break;
		case 2:
			cur_pos.x += 400.0f * Time::DeltaTime();
			cur_pos.y += 400.0f * Time::DeltaTime();
			break;		 
		case 3:			 
			cur_pos.x += 400.0f* Time::DeltaTime();
			cur_pos.y -= 400.0f* Time::DeltaTime();
			break;		 
		case 4:			 
			cur_pos.y -= 400.0f * Time::DeltaTime();
			break;		 
		case 5:			 
			cur_pos.x += 400.0f * Time::DeltaTime();
			break;
		case 6:			 
			cur_pos.x -= 400.0f * Time::DeltaTime();
			break;
		case 7:			 
			cur_pos.y += 400.0f * Time::DeltaTime();
			break;	
		}
		tr->SetPosition(cur_pos);
		following_time -= Time::DeltaTime();
		if (following_time <= 0.0f)
		{
			Destroy(this);
		}
	}

	int GanonFireBats::CheckPlayerPos()
	{
		int type = 0;
		Vector2 cur_pos = tr->GetPosition();
		if (Player_Pos.x < cur_pos.x && Player_Pos.y < cur_pos.y)
			type = 0;
		else if (Player_Pos.x < cur_pos.x && Player_Pos.y > cur_pos.y)
			type = 1;
		else if (Player_Pos.x > cur_pos.x && Player_Pos.y > cur_pos.y)
			type = 2;
		else if (Player_Pos.x > cur_pos.x && Player_Pos.y < cur_pos.y)
			type = 3;


		return type;
	}
}