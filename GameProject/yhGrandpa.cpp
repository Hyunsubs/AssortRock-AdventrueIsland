#include "yhGrandpa.h"
#include "yhAnimator.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhInput.h"
#include "yhAsciiRender.h"
#include "yhObject.h"
#include "yhPlayer.h"

namespace yh
{
	Grandpa::Grandpa() :
		  anim(nullptr)
		, tr(nullptr)
		, col(nullptr)
		, dialogue({})
		, ascii(nullptr)
		, idx(0)
	{
		anim = AddComponent<Animator>();
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();
	}
	Grandpa::~Grandpa()
	{
	}
	void Grandpa::Initialize()
	{
		std::wstring npc_path = NPC_PATH;
		col->SetSize(Vector2(25.0f, 25.0f));
		anim->CreateAnimationFolder(L"GrandpaNPC",npc_path + L"Grandpa",Vector2::Zero,0.5f);
		anim->SetScale(Vector2(2.0f, 2.0f));
		anim->PlayAnimation(L"GrandpaNPC", true);

		Vector2 my_pos = tr->GetPosition();
		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Vector2(my_pos.x - 100.0f, my_pos.y + 250.0f));
		ascii->SetString("HI LINK\nYOU HAVE TO SAVE \nPRINCESS ZELDA");
		ascii->PrintAsciis();
		ascii->Destroy();
		dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Vector2(my_pos.x - 100.0f, my_pos.y + 250.0f));
		ascii->SetString("YOU HAVE TO GET\nTHE SWORD\nIN THE FOREST");
		ascii->PrintAsciis();
		ascii->Destroy();
		dialogue.push_back(ascii);

		ascii = object::Instantiate<AsciiRender>(eLayerType::Asciis, Vector2(my_pos.x - 100.0f, my_pos.y + 250.0f));
		ascii->SetString("GOOD LUCK\nMAY THE FORCE\nBE WITH YOU");
		ascii->PrintAsciis();
		ascii->Destroy();
		dialogue.push_back(ascii);

	}
	void Grandpa::Update()
	{
		GameObject::Update();
	}
	void Grandpa::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Grandpa::OnCollisionEnter(Collider* other)
	{
	}
	void Grandpa::OnCollisionStay(Collider* other)
	{

		if (Input::GetKeyDown(eKeyCode::I))
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());
			if (player == nullptr)
				return;
			if (idx >= 3)
			{
				player->SetState(Player::PlayerState::Idle);
				dialogue[idx - 1]->Destroy();
				idx = 0;
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
	void Grandpa::OnCollisionExit(Collider* other)
	{
	}
}