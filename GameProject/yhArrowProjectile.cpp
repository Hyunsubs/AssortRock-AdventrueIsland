#include "yhArrowProjectile.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhTime.h"
#include "yhPlayer.h"
#include "yhAnimator.h"

namespace yh
{
	ArrowProjectile::ArrowProjectile() :
		  tr(nullptr)
		, image(nullptr)
		, flying_time(1.5f)
		, direct(Directions::End)
		, col(nullptr)
		, sr(nullptr)
	{
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();
		sr = AddComponent<SpriteRenderer>();

	}
	ArrowProjectile::~ArrowProjectile()
	{
	}
	void ArrowProjectile::Initialize()
	{
	}
	void ArrowProjectile::Update()
	{
		GameObject::Update();
		std::wstring monster_path = MONSTER_PATH;
		flying_time -= Time::DeltaTime();
		Vector2 cur_pos = tr->GetPosition();
		switch (direct)
		{
		case yh::enums::Directions::Forward:
			image = Resources::Load<Texture>(L"ForwardArrow", monster_path + L"BlueKnight\\Arrow\\ArrowForward.bmp");
			cur_pos.y -= 250.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Backward:
			image = Resources::Load<Texture>(L"BackwardArrow", monster_path + L"BlueKnight\\Arrow\\ArrowBackward.bmp");
			cur_pos.y += 250.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Left:
			image = Resources::Load<Texture>(L"LeftArrow", monster_path + L"BlueKnight\\Arrow\\ArrowLeft.bmp");
			cur_pos.x -= 250.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Right:
			image = Resources::Load<Texture>(L"RightArrow", monster_path + L"BlueKnight\\Arrow\\ArrowRight.bmp");
			cur_pos.x += 250.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::End:
			break;
		default:
			break;
		}
		tr->SetPosition(cur_pos);
		sr->SetImage(image);
		sr->SetScale(Vector2::Double);
		if (flying_time <= 0.0f)
			Destroy(this);

	}
	void ArrowProjectile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ArrowProjectile::OnCollisionEnter(Collider* other)
	{
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
			Destroy(this);
		}
	}
	void ArrowProjectile::OnCollisionStay(Collider* other)
	{
	}
	void ArrowProjectile::OnCollisionExit(Collider* other)
	{
	}
}