#include "yhChicken.h"
#include "yhTransform.h"
#include "yhAnimator.h"
#include "yhCollider.h"
#include "yhPlayerSword.h"
#include "yhTime.h"
#include "yhPlayer.h"
#include "yhCamera.h"
#include "yhObject.h"
#include "yhTexture.h"

namespace yh
{
	Chicken::Chicken() :
		  tr(nullptr)
		, anim(nullptr)
		, hit_count(0)
		, col(nullptr)
		, state(ChickenState::Moving)
		, direct(Directions::Left)
		, move_count(0)
		, move_time(1.0f)
		, PixelTexture(nullptr)
		, map_size(Vector2::Zero)
	{
		srand(time(NULL));
		rand_num = rand() % 12;

		tr = GetComponent<Transform>();
		anim = AddComponent<Animator>();
		col = AddComponent<Collider>();
		col->SetSize(Vector2(20.0f, 20.0f));

		anim->CreateAnimationFolder(L"ChickenIdleLeftAnim", L"..\\Resources\\Image\\Chicken\\IdleLeft");
		anim->CreateAnimationFolder(L"ChickenIdleRightAnim", L"..\\Resources\\Image\\Chicken\\IdleRight");
		anim->CreateAnimationFolder(L"ChickenAttackLeftAnim", L"..\\Resources\\Image\\Chicken\\AttackedLeft");
		anim->CreateAnimationFolder(L"ChickenAttackRightAnim", L"..\\Resources\\Image\\Chicken\\AttackedRight");

		make_pos_arr[0] = Vector2(180.0f, 180.0f);
		make_pos_arr[1] = Vector2(150.0f, 100.0f);
		make_pos_arr[2] = Vector2(120.0f, 50.0f);
		make_pos_arr[3] = Vector2(-180.0f, -180.0f);
		make_pos_arr[4] = Vector2(-100.0f, 100.0f);
		make_pos_arr[5] = Vector2(-100.0f, -100.0f);
		make_pos_arr[6] = Vector2(120.0f, -120.0f);
		make_pos_arr[7] = Vector2(300.0f, -200.0f);
		make_pos_arr[8] = Vector2(400.0f, 250.0f);
		make_pos_arr[9] = Vector2(300.0f, -180.0f);
		make_pos_arr[10] = Vector2(250.0f, 250.0f);
		make_pos_arr[11] = Vector2(-200.0f, 180.0f);

		anim->SetScale(Vector2::Double);
		anim->PlayAnimation(L"ChickenIdleLeftAnim", true);
	}
	Chicken::~Chicken()
	{
	}
	void Chicken::Initialize()
	{
	}
	void Chicken::Update()
	{
		GameObject::Update();

		if (state != ChickenState::Flying)
		{
			CheckPixel(PixelTexture, map_size);
		}

		switch (state)
		{
		case yh::ChickenState::Moving:
			Moving();
			break;
		case yh::ChickenState::Attacked:
			Attack();
			break;
		case yh::ChickenState::Angry:
			Angry();
			break;
		case yh::ChickenState::Flying:
			Flying();
			break;
		default:
			break;
		}
	}
	void Chicken::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Chicken::Moving()
	{
		Vector2 cur_pos = tr->GetPosition();
		move_time += Time::DeltaTime();
		if (move_time >= 1.0f)
		{
			move_time = 0.0f;
			move_count++;
		}

		if (move_count >= 3)
		{
			switch (direct)
			{
			case yh::enums::Directions::Left:
				direct = Directions::Right;
				break;
			case yh::enums::Directions::Right:
				direct = Directions::Left;
				break;
			}
		}

		switch (direct)
		{
		case yh::enums::Directions::Left:
			cur_pos.x -= 50.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Right:
			cur_pos.x += 50.0f * Time::DeltaTime();
			break;
		default:
			break;
		}
		tr->SetPosition(cur_pos);
	}
	void Chicken::Attack()
	{
		Vector2 cur_pos = tr->GetPosition();
		switch (direct)
		{
		case yh::enums::Directions::Left:
			cur_pos.x -= 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Right:
			cur_pos.x += 100.0f * Time::DeltaTime();
			break;
		default:
			break;
		}
		tr->SetPosition(cur_pos);
	}

	void Chicken::Angry()
	{
		rand_num = rand() % 12;
		Chicken* chic = object::Instantiate<Chicken>(eLayerType::Chicken, Camera::CalculateUIPosition(tr->GetPosition() + make_pos_arr[rand_num]));
		chic->SetChickenState(ChickenState::Flying);
	}

	void Chicken::Flying()
	{
		Vector2 cur_pos = tr->GetPosition();
		if (cur_pos.x > player_pos.x)
			cur_pos.x -= 200.0f * Time::DeltaTime();
		else
			cur_pos.x += 200.0f * Time::DeltaTime();
		if (cur_pos.y > player_pos.y)
			cur_pos.y -= 200.0f * Time::DeltaTime();
		else
			cur_pos.y += 200.0f * Time::DeltaTime();
		tr->SetPosition(cur_pos);
	}


	void Chicken::OnCollisionEnter(Collider* other)
	{
		PlayerSword* sword = dynamic_cast<PlayerSword*>(other->GetOwner());
		if (sword != nullptr)
		{
			state = ChickenState::Attacked;
			hit_count++;
			if (hit_count >= 5)
			{
				state = ChickenState::Angry;
				switch (direct)
				{
				case yh::enums::Directions::Left:
					anim->PlayAnimation(L"ChickenAttackLeftAnim", true);
					break;
				case yh::enums::Directions::Right:
					anim->PlayAnimation(L"ChickenAttackRightAnim", true);
					break;
				}
			}
			return;
		}

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr && state == ChickenState::Flying)
		{
			int player_hp = player->GetHp();
			player_hp--;
			player->SetHp(player_hp);
			Destroy(this);
		}
	}
	void Chicken::OnCollisionStay(Collider* other)
	{
	}
	void Chicken::OnCollisionExit(Collider* other)
	{
	}



	void Chicken::CheckPixel(Texture* pixel_texture, Vector2 map_size)
	{
		if (pixel_texture == nullptr)
			return;
		std::vector<COLORREF> rgbs;
		Transform* my_tr = tr;
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
					my_pos.y -= 3.0f;
					break;
				case 1:
					my_pos.y += 3.0f;
					break;
				case 2:
					my_pos.x += 3.0f;
					break;
				case 3:
					my_pos.x -= 3.0f;
					break;
				default:
					break;
				}
				my_tr->SetPosition(my_pos);
			}

		}
	}

}