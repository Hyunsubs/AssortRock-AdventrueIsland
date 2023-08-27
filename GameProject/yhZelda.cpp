#include "yhZelda.h"
#include "yhAnimator.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhInput.h"
#include "yhAsciiRender.h"
#include "yhObject.h"
#include "yhPlayer.h"
#include "yhResources.h"
#include "yhSound.h"

namespace yh
{
	Zelda::Zelda()
	{
		anim = AddComponent<Animator>();
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();
	}
	Zelda::~Zelda()
	{
	}


	void Zelda::Initialize()
	{
		wstring npc_path = NPC_PATH;
		wstring sound_path = SOUND_PATH;
		col->SetSize(Vector2(25.0f, 25.0f));
		anim->CreateAnimationFolder(L"Zelda", npc_path + L"Zelda\\Idle", Vector2::Zero, 0.5f);
		anim->SetScale(Vector2(2.0f, 2.0f));
		anim->PlayAnimation(L"ZeldaNPC", true);

		Vector2 my_pos = tr->GetPosition();
		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Vector2(my_pos.x - 100.0f, my_pos.y + 250.0f));
		ascii->SetString("THANK YOU LINK");
		ascii->PrintAsciis();
		ascii->Destroy();
		dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Vector2(my_pos.x - 100.0f, my_pos.y + 250.0f));
		ascii->SetString("LETS GO HOME TOGETHER");
		ascii->PrintAsciis();
		ascii->Destroy();
		dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Vector2(my_pos.x - 100.0f, my_pos.y + 250.0f));
		ascii->SetString("MY LOVE");
		ascii->PrintAsciis();
		ascii->Destroy();
		dialogue.push_back(ascii);

		end_sound = Resources::Load<Sound>(L"EndingSound",sound_path + L"Ending.wav");

	}
	void Zelda::Update()
	{
		GameObject::Update();
	}
	void Zelda::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Zelda::OnCollisionEnter(Collider* other)
	{
	}
	void Zelda::OnCollisionStay(Collider* other)
	{

		if (Input::GetKeyDown(eKeyCode::I) && GetState() == eState::Active)
		{
			if (!end_played)
			{
				end_sound->Play(false);
				end_played = true;
			}

			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (player == nullptr)
				return;
			if (idx >= 3)
			{
				player->SetState(Player::PlayerState::Idle);
				dialogue[idx - 1]->Destroy();
				idx = 0;
				Destroy(this);
			}
			else if (idx == 0)
			{
				player->SetState(Player::PlayerState::Talking);
				dialogue[idx]->Activate();
				idx++;
			}
			else
			{
				dialogue[idx - 1]->Destroy();
				dialogue[idx]->Activate();
				idx++;
			}
		}

	}

	void Zelda::OnCollisionExit(Collider* other)
	{
	}
	
}