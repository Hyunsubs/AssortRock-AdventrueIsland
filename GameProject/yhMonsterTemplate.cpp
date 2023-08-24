#include "yhMonsterTemplate.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhCollider.h"
#include "yhTime.h"
#include "yhPlayer.h"
namespace yh
{
	MonsterTemplate::MonsterTemplate() :
		  PixelTexture(nullptr)
		, col(nullptr)
		, direction(Directions::End)
		, is_Wall(false)
		, anim(nullptr)
		, tr(nullptr)
		, state(MonsterState::End)
		, knock_back_time(0.5f)
		, clutch_time(0.5f)
	{
	
	}

	MonsterTemplate::~MonsterTemplate()
	{

	}

	void MonsterTemplate::Initialize()
	{
	}

	void MonsterTemplate::Update()
	{
		CheckPixel(PixelTexture, map_size);
		GameObject::Update();

	}

	void MonsterTemplate::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}



	void MonsterTemplate::OnCollisionEnter(Collider* other)
	{
		if (state == MonsterState::End)
			return;
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr && state != MonsterState::Death && !(player->GetIsHit()))
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
	void MonsterTemplate::OnCollisionStay(Collider* other)
	{
	}
	void MonsterTemplate::OnCollisionExit(Collider* other)
	{
	}


	void MonsterTemplate::Idle()
	{
	}




	void MonsterTemplate::Move()
	{
	}

	void MonsterTemplate::MoveReady()
	{

	}


	void MonsterTemplate::Attack()
	{
	}



	void MonsterTemplate::Death()
	{
		if (anim->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void MonsterTemplate::KnockBack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 cur_pos = tr->GetPosition();
		knock_back_time -= Time::DeltaTime();
		if (knock_back_time <= 0.0f)
		{
			knock_back_time = 0.5f;
			state = MonsterState::Idle;
		}
		else
		{
			tr->SetPosition(Vector2(cur_pos.x, cur_pos.y - 80.0f * Time::DeltaTime()));
		}


	}



	void MonsterTemplate::Falling()
	{
	}



	void MonsterTemplate::Ui()
	{
	}



	void MonsterTemplate::Chasing()
	{
	}


	void MonsterTemplate::CheckChasing()
	{
	}


	void MonsterTemplate::CheckPixel(Texture* pixel_texture, Vector2 map_size)
	{
		if (pixel_texture == nullptr)
			return;
		std::vector<COLORREF> rgbs;
		Transform* my_tr = GetComponent<Transform>();
		COLORREF down_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x, my_tr->GetPosition().y + map_size.y + 16);
		COLORREF up_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x, my_tr->GetPosition().y + map_size.y - 16);
		COLORREF left_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x - 16, my_tr->GetPosition().y + map_size.y);
		COLORREF right_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x + 16, my_tr->GetPosition().y + map_size.y);

		rgbs.push_back(down_color);
		rgbs.push_back(up_color);
		rgbs.push_back(left_color);
		rgbs.push_back(right_color);

		for (int i = 0; i < 4; ++i)
		{
			if (rgbs[i] == RGB(0, 0, 255))
			{
				Vector2 my_pos = my_tr->GetPosition();
				switch (i)
				{
				case 0:
					my_pos.y -= 3.0f /* Time::DeltaTime()*/;
					break;
				case 1:
					my_pos.y += 3.0f /*Time::DeltaTime()*/;
					break;
				case 2:
					my_pos.x += 3.0f /* Time::DeltaTime()*/;
					break;
				case 3:
					my_pos.x -= 3.0f  /*Time::DeltaTime()*/;
					break;
				default:
					break;
				}
				is_Wall = true;
				my_tr->SetPosition(my_pos);
			}

			else
			{
				is_Wall = false;
			}
		}
	}



}