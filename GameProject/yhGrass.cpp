#include "yhGrass.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhCollider.h"
#include "yhResources.h"
#include "yhTexture.h"
#include "yhPlayer.h"
#include "yhInput.h"
#include "yhAnimator.h"
#include "yhTime.h"
#include "yhPlayerSword.h"
#include "yhMonsterTemplate.h"
#include "yhGreenKnight.h"
#include "yhEmptyGrass.h"
#include "yhObject.h"
#include "yhPlayerGrass.h"

namespace yh
{
	Grass::Grass() :
		  sr(nullptr)
		, tr(nullptr)
		, image(nullptr)
		, col(nullptr)
		, flying_time(0.3f)
		, state(grass_state::Idle)
		, direct(Directions::Forward)
		, is_destyoed(false)
	{

	}


	Grass::~Grass()
	{
	}


	void Grass::Initialize()
	{
		std::wstring tile_path = TILE_PATH;
		std::wstring inter_path = INTERACTION_PATH;
		name = L"Grass";
		path = tile_path + L"new_grass_tile.bmp";

		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		col = AddComponent<Collider>();
		anim = AddComponent<Animator>();
		anim->CreateAnimationFolder(L"GrassThrownAnim", inter_path + L"Link_Grass_Throwing",Vector2(0.0f,0.0f),0.05f);


		image = Resources::Load<Texture>(name, path);
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
		col->SetSize(Vector2(28.0f, 28.0f));
	}

	void Grass::Update()
	{
		GameObject::Update();

		switch (state)
		{
		case yh::grass_state::Idle:
			
			break;
		case yh::grass_state::Flying:
			GrassMoving(direct);
			break;
		case yh::grass_state::Destroyed:
			DestroyAnim();
			break;
		case yh::grass_state::Death:
			Death();
			break;
		default:
			break;
		}
	}

	void Grass::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Grass::OnCollisionEnter(Collider* other)
	{
		Vector2 cur_pos = tr->GetPosition();
		PlayerSword* player_sword = dynamic_cast<PlayerSword*>(other->GetOwner());
		if (player_sword != nullptr && player_sword->GetSwordState() == PlayerSword::SwordState::Attack && !is_destyoed)
		{
			is_destyoed = true;
			state = grass_state::Destroyed;
			object::Instantiate<EmptyGrass>(eLayerType::Background, cur_pos);
		}
		
		MonsterTemplate* monster = dynamic_cast<MonsterTemplate*>(other->GetOwner());
		if (state == grass_state::Flying && monster != nullptr)
		{
			int monster_hp = monster->GetHp();
			monster_hp -= 1;
			monster->SetHp(monster_hp);
			is_destyoed = true;
			state = grass_state::Destroyed;
		}

		GreenKnight* gn = dynamic_cast<GreenKnight*>(other->GetOwner());
		if (gn != nullptr)
		{
			int gn_hp = gn->GetHp();
			gn_hp -= 1;
			gn->SetHp(gn_hp);
			is_destyoed = true;
			state = grass_state::Destroyed;
		}
	}

	void Grass::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Animator* player_anim = player->GetComponent<Animator>();
			Transform* player_tr = player->GetComponent<Transform>();

			if (Input::GetKeyDown(eKeyCode::K) && !(player->GetThrowing()) && (player->GetGrass()->GetState() == GameObject::eState::Pause))
			{
				Vector2 cur_pos = tr->GetPosition();
				player->GetGrass()->SetState(GameObject::eState::Active);
				Destroy(this);
				object::Instantiate<EmptyGrass>(eLayerType::Background,cur_pos);
			}

		}
	}

	void Grass::OnCollisionExit(Collider* other)
	{
	}


	void Grass::GrassMoving(Directions direct)
	{
		flying_time -= Time::DeltaTime();
		Vector2 my_pos = tr->GetPosition();

		switch (direct)
		{
		case yh::enums::Directions::Forward:
		case yh::enums::Directions::UpRight:
		case yh::enums::Directions::UpLeft:
			my_pos.y -= 300.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Backward:
		case yh::enums::Directions::DownRight:
		case yh::enums::Directions::DownLeft:
			my_pos.y += 300.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Left:
			my_pos.x -= 300.0f * Time::DeltaTime();
			my_pos.y += 60.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Right:
			my_pos.x += 300.0f * Time::DeltaTime();
			my_pos.y += 60.0f * Time::DeltaTime();
			break;
		default:
			break;
		}
		tr->SetPosition(my_pos);
		
		if (flying_time <= 0.0f)
		{
			state = grass_state::Destroyed;
			flying_time = 0.3f;
		}
	}


	void Grass::DestroyAnim()
	{
		image = nullptr;
		sr->SetImage(image);
		anim->SetScale(Vector2(2.0f, 2.0f));
		anim->PlayAnimation(L"GrassThrownAnim",false);
		state = grass_state::Death;
	}

	void Grass::Death()
	{
		if (anim->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	
}