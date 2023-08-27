#include "yhGroundSword.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhAsciiRender.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhObject.h"
#include "yhPlayer.h"
#include "yhCollider.h"
#include "yhAnimator.h"
#include "yhInput.h"
#include "yhSound.h"

namespace yh
{
	GroundSword::GroundSword() :
		  ar(nullptr)
		, image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
		, col(nullptr)
		, sound_played(false)
	{
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		col = AddComponent<Collider>();

		col->SetSize(Vector2(32.0f, 32.0f));


		image = Resources::Load<Texture>(L"GroundSword", L"..\\Resources\\Image\\GroundSword\\ground_sword.bmp");
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));

		Vector2 sword_tr = tr->GetPosition();
		ar = object::Instantiate<AsciiRender>(eLayerType::Asciis,Vector2(sword_tr.x, sword_tr.y + 170.0f));
		ar->SetString("YOU GOT A SWORD\nPRESS J TO ATTACK");
		ar->PrintAsciis();
		ar->Destroy();

		wstring sound_path = SOUND_PATH;
		get_sound = Resources::Load<Sound>(L"GetItemSound", sound_path + L"item_get.wav");
	}
	GroundSword::~GroundSword()
	{
	}
	void GroundSword::Initialize()
	{


	}
	void GroundSword::Update()
	{
		GameObject::Update();

	}
	void GroundSword::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GroundSword::OnCollisionEnter(Collider* other)
	{
	


	}
	void GroundSword::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (!sound_played)
			{
				sound_played = true;
				get_sound->Play(false);
			}

			Animator* player_anim = player->GetComponent<Animator>();
			player_anim->PlayAnimation(L"LinkGetItem", false);
			player->SetState(Player::PlayerState::Talking);
			player->SetIsSword(true);

			Transform* player_tr = player->GetComponent<Transform>();
			Vector2 cur_pos = player_tr->GetPosition();
			tr->SetPosition(Vector2(cur_pos.x, cur_pos.y - 30.0f));
			image = Resources::Load<Texture>(L"gotsword", L"..\\Resources\\Image\\GroundSword\\get_sword.bmp");
			sr->SetImage(image);

			ar->Activate();

			if (Input::GetKeyDown(eKeyCode::I))
			{
				player->SetState(Player::PlayerState::Idle);
				ar->Destroy();
				Destroy(this);
			}

		}
	}
	void GroundSword::OnCollisionExit(Collider* other)
	{
	}
}