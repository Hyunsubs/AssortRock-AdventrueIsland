#include "yhHeartContainer.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhTexture.h"
#include "yhCollider.h"
#include "yhResources.h"
#include "yhPlayer.h"
#include "yhCamera.h"
#include "yhObject.h"
#include "yhAsciiRender.h"
#include "yhAnimator.h"
#include "yhInput.h"
#include "yhSound.h"

namespace yh
{
	HeartContainer::HeartContainer() :
		  image(nullptr)
		, col(nullptr)
		, sr(nullptr)
		, tr(nullptr)
		, sound_played(false)
		, get_sound(nullptr)

	{
		wstring ground_item_path = GROUND_ITEM_PATH;
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();
		sr = AddComponent<SpriteRenderer>();
		image = Resources::Load<Texture>(L"HeartContainerImage", ground_item_path + L"HeartContainer.bmp");
		sr->SetImage(image);
		sr->SetScale(Vector2::Double);
		col->SetSize(Vector2(20.0f,20.0f));

		wstring sound_path = SOUND_PATH;
		get_sound = Resources::Load<Sound>(L"ItemGetSound", sound_path + L"item_get.wav");

		Vector2 container_tr = tr->GetPosition();
		ar = object::Instantiate<AsciiRender>(eLayerType::Asciis, Camera::CalculateUIPosition(Vector2(-30.0f, 170.0f)));
		ar->SetString("YOU GOT A HEART CONTAINER\nMAX HP INCREASED\nALSO HP MAX");
		ar->Destroy();
	}
	HeartContainer::~HeartContainer()
	{
	}
	void HeartContainer::Initialize()
	{
	}
	void HeartContainer::Update()
	{
		GameObject::Update();
	}
	void HeartContainer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HeartContainer::OnCollisionEnter(Collider* other)
	{
		
	}
	void HeartContainer::OnCollisionStay(Collider* other)
	{
		if (!sound_played)
		{
			get_sound->Play(false);
			sound_played = true;
		}

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* ar_tr = ar->GetComponent<Transform>();
			ar_tr->SetPosition(Camera::CalculateUIPosition(Vector2(256.0f, 400.0f)));
			
			if (player->GetState() != Player::PlayerState::Talking)
			{
				ar->PrintAsciis();
				col->SetSize(Vector2(30.0f, 200.0f));
				int max_hp = player->GetMaxHp();
				max_hp++;
				player->SetMaxHp(max_hp);
				player->SetHp(max_hp);
				Animator* player_anim = player->GetComponent<Animator>();
				player_anim->PlayAnimation(L"LinkGetItem", false);
				player->SetState(Player::PlayerState::Talking);

				Transform* player_tr = player->GetComponent<Transform>();
				Vector2 cur_pos = player_tr->GetPosition();
				tr->SetPosition(Vector2(cur_pos.x, cur_pos.y - 30.0f));

				ar->Activate();
			}

			if (Input::GetKeyDown(eKeyCode::I))
			{
				player->SetState(Player::PlayerState::Idle);
				ar->Destroy();
				Destroy(this);
			}

		}
	}
	void HeartContainer::OnCollisionExit(Collider* other)
	{
	}
}