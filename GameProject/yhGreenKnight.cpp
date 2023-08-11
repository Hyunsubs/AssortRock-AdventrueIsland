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
		state(MonsterState::Idle)
		, direction(Directions::Backward)
		, moving_time(2.0f)
		, tr(nullptr)
		, is_chasing(false)
		, is_Wall(false)

	{
		std::wstring monster_path = MONSTER_PATH;
		anim = AddComponent<Animator>();
		col = AddComponent<Collider>();
		tr = GetComponent<Transform>();

		//평소 움직임
		anim->CreateAnimationFolder(L"GnMovingBackward", monster_path + L"GreenKnight\\Moving\\Backward", Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"GnMovingForward", monster_path + L"GreenKnight\\Moving\\Forward", Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"GnMovingLeft", monster_path + L"GreenKnight\\Moving\\Left", Vector2::Zero, 0.3f);
		anim->CreateAnimationFolder(L"GnMovingRight", monster_path + L"GreenKnight\\Moving\\Right", Vector2::Zero, 0.3f);

		//빠르게 따라가기
		anim->CreateAnimationFolder(L"GnChasingBackward", monster_path + L"GreenKnight\\Moving\\Backward", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"GnChasingForward", monster_path + L"GreenKnight\\Moving\\Forward", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"GnChasingLeft", monster_path + L"GreenKnight\\Moving\\Left", Vector2::Zero, 0.1f);
		anim->CreateAnimationFolder(L"GnChasingRight", monster_path + L"GreenKnight\\Moving\\Right", Vector2::Zero, 0.1f);
		col->SetSize(Vector2(30.0f, 30.0f));
		anim->SetScale(Vector2(2.0f, 2.0f));

		//떨어질때
		anim->CreateAnimationFolder(L"GnFalling", monster_path + L"GreenKnight\\Falling", Vector2::Zero, 0.3f);


		//둘러보기
		anim->CreateAnimationFolder(L"GnLookBackward", monster_path + L"GreenKnight\\LookAround\\Backward", Vector2::Zero, 0.15f);
		anim->CreateAnimationFolder(L"GnLookForward", monster_path + L"GreenKnight\\LookAround\\Forward", Vector2::Zero, 0.15f);
		anim->CreateAnimationFolder(L"GnLookLeft", monster_path + L"GreenKnight\\LookAround\\Left", Vector2::Zero, 0.15f);
		anim->CreateAnimationFolder(L"GnLookRight", monster_path + L"GreenKnight\\LookAround\\Right", Vector2::Zero, 0.15f);

		//죽을때
		anim->CreateAnimationFolder(L"GnDeath", monster_path + L"GreenKnight\\Dead",Vector2::Zero, 0.3f);

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
		CheckPixel(PixelTexture, map_size);
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
			Death();
			break;
		case yh::MonsterState::Falling:
			Falling();
			break;
		case yh::MonsterState::Chasing:
			Chasing();
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
		if (player != nullptr)
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
				player_anim->PlayAnimation(L"LinkHitForward",false);
				break;
			case Directions::Backward:
				player_anim->PlayAnimation(L"LinkHitBackward",false);
				break;
			case Directions::Left:
				player_anim->PlayAnimation(L"LinkHitLeft",false);
				break;
			case Directions::Right:
				player_anim->PlayAnimation(L"LinkHitRight",false);
				break;
			default:
				break;
			}
			
		}



	}
	void GreenKnight::OnCollisionStay(Collider* other)
	{
	}
	void GreenKnight::OnCollisionExit(Collider* other)
	{
	}

	void GreenKnight::Idle()
	{
		CheckChasing();

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

		if (is_chasing)
		{
			state = MonsterState::Chasing;
		}

	}


	void GreenKnight::Move()
	{
		CheckChasing();

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
			if (!is_Wall)
			{
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
	}

	void GreenKnight::Attack()
	{
	}

	void GreenKnight::Death()
	{
		if (anim->IsActiveAnimationComplete())
			Destroy(this);
	}

	void GreenKnight::Falling()
	{
		if (anim->IsActiveAnimationComplete())
			Destroy(this);
	}

	void GreenKnight::Ui()
	{
	}

	void GreenKnight::Chasing()
	{
		if (anim->IsActiveAnimationComplete())
		{
			CheckChasing();
		}


		//6가지 상황
		//플레이어 기준 좌측위에 있을때
		Vector2 my_pos = tr->GetPosition();
		if (!is_Wall)
		{
			//플레이어 기준 좌측
			if (player_pos.x - my_pos.x > 0 && abs(player_pos.y - my_pos.y) < 80.0f)
			{
				direction = Directions::Right;
				my_pos.x += 50.0f * Time::DeltaTime();
				if (player_pos.y > my_pos.y)
				{
					my_pos.y += 50.0f * Time::DeltaTime();
				}
				else
				{
					my_pos.y -= 50.0f * Time::DeltaTime();
				}

			}

			//플레이어 기준 우측
			else if (player_pos.x - my_pos.x < 0 && abs(player_pos.y - my_pos.y) < 80.0f)
			{
				direction = Directions::Left;
				my_pos.x -= 80.0f * Time::DeltaTime();
				if (player_pos.y > my_pos.y)
				{
					my_pos.y += 80.0f * Time::DeltaTime();
				}
				else
				{
					my_pos.y -= 80.0f * Time::DeltaTime();
				}

			}

			else if (player_pos.x - my_pos.x > 0 && player_pos.y - my_pos.y < 0)
			{
				direction = Directions::Forward;
				my_pos.x += 80.0f * Time::DeltaTime();
				my_pos.y -= 80.0f * Time::DeltaTime();

			}
			//플레이어 기준 우측 위에 있을때
			else if (player_pos.x - my_pos.x < 0 && player_pos.y - my_pos.y < 0)
			{
				direction = Directions::Forward;
				my_pos.x -= 80.0f * Time::DeltaTime();
				my_pos.y -= 80.0f * Time::DeltaTime();

			}
			//플레이어 기준 우측 아래 있을때
			else if (player_pos.x - my_pos.x < 0 && player_pos.y - my_pos.y > 0)
			{
				direction = Directions::Backward;
				my_pos.x -= 80.0f * Time::DeltaTime();
				my_pos.y += 80.0f * Time::DeltaTime();


			}
			//플레이어 기준 좌측 아래 있을때
			else if (player_pos.x - my_pos.x > 0 && player_pos.y - my_pos.y > 0)
			{
				direction = Directions::Backward;
				my_pos.x += 80.0f * Time::DeltaTime();
				my_pos.y += 80.0f * Time::DeltaTime();

			}


			tr->SetPosition(my_pos);
		}

		if (!is_chasing)
			state = MonsterState::Idle;
	}



	void GreenKnight::CheckChasing()
	{
		if (is_chasing)
		{
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				anim->PlayAnimation(L"GnChasingForward");
				break;
			case yh::enums::Directions::Backward:
				anim->PlayAnimation(L"GnChasingBackward");
				break;
			case yh::enums::Directions::Left:
				anim->PlayAnimation(L"GnChasingLeft");
				break;
			case yh::enums::Directions::Right:
				anim->PlayAnimation(L"GnChasingRight");
				break;
			case yh::enums::Directions::End:
				break;
			default:
				break;
			}
			state = MonsterState::Chasing;
		}
	}

	void GreenKnight::CheckPixel(Texture* pixel_texture, Vector2 map_size)
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

	
