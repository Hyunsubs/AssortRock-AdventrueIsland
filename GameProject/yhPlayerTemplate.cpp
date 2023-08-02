#include "yhPlayerTemplate.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhObject.h"
#include "yhInput.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhInput.h"
#include "yhTexture.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhBackGround.h"
#include "yhCamera.h"
#include "yhSceneChanger.h"
#include "yhPlayerSword.h"
#include "yhManaPoint.h"
#include "yhMana.h"
#include "yhHpInterface.h"
#include "yhLifeUI.h"
#include "yhArrow.h"
#include "yhBomb.h"
#include "yhRupeeUI.h"
#include "yhCurItem.h"

namespace yh
{
	PlayerTemplate::PlayerTemplate() : mana(nullptr)
									 , manapoints(nullptr)
						             , player(nullptr)
									 , sword(nullptr)
	{
	}
	PlayerTemplate::~PlayerTemplate()
	{
	}
	void PlayerTemplate::Initialize()
	{
		//ȭ�� ���氡���� ��ü����
		object::Instantiate<SceneChanger>(eLayerType::Background);
		//�÷��̾� ����
		player = object::Instantiate<Player>(eLayerType::Player, Vector2(256.0f, 256.0f));
		//���� UI
		mana = object::Instantiate<Mana>(eLayerType::UI);
		//life �۾�
		life = object::Instantiate<LifeUI>(eLayerType::UI);
		life->SetState(GameObject::eState::Active);
		//ȭ�� ���� UI
		arrow = object::Instantiate<Arrow>(eLayerType::UI);
		arrow->SetState(GameObject::eState::Active);
		//��ź ���� UI
		bomb = object::Instantiate<Bomb>(eLayerType::UI);
		bomb->SetState(GameObject::eState::Active);
		//���� ���� UI
		rupee_ui = object::Instantiate<RupeeUI>(eLayerType::UI);
		rupee_ui->SetState(GameObject::eState::Active);
		//���� ������ UI
		cur_item = object::Instantiate<CurItem>(eLayerType::UI);
		cur_item->SetState(GameObject::eState::Active);

		//ü��UI �ν��Ͻ�ȭ �� ���Ϳ� �߰�
		for (int i = 0; i < player->GetMaxHp(); i++)
		{
			HpInterface* hp = object::Instantiate<HpInterface>(eLayerType::UI);
			hp_container.push_back(hp);
		}
	}
	void PlayerTemplate::Update(Vector2 pos)
	{
		Scene::Update();
		//HP ȭ�鿡 ����

		for (int i = 0; i < player->GetHp(); i++)
		{
			if (hp_container[i]->GetState() == GameObject::eState::Dead || hp_container[i]->GetState() == GameObject::eState::Pause)
			{
				hp_container[i]->SetState(GameObject::eState::Active);
			}

			Transform* tr = hp_container[i]->GetComponent<Transform>();
			tr->SetPosition(Camera::CalculateUIPosition(Vector2(340.0f + i * 15, 70.0f)));
		}

		//������ ���� ����
		Transform* life_tr = life->GetComponent<Transform>();
		life_tr->SetPosition(Camera::CalculateUIPosition(Vector2(400.0f, 50.0f)));

		//ȭ�� UI ����
		Transform* arrow_tr = arrow->GetComponent<Transform>();
		arrow_tr->SetPosition(Camera::CalculateUIPosition(Vector2(240.0f, 60.0f)));

		//��ź UI ����
		Transform* bomb_tr = bomb->GetComponent<Transform>();
		bomb_tr->SetPosition(Camera::CalculateUIPosition(Vector2(190.0f, 60.0f)));

		//���� UI ����
		Transform * rupee_tr = rupee_ui->GetComponent<Transform>();
		rupee_tr->SetPosition(Camera::CalculateUIPosition(Vector2(140.0f, 60.0f)));

		//���� ������ UI ����
		Transform* cur_item_tr = cur_item->GetComponent<Transform>();
		cur_item_tr->SetPosition(Camera::CalculateUIPosition(Vector2(67.0f,30.0f)));


		//MP �������̽�
		Transform* mana_tr = mana->GetComponent<Transform>();
		mana_tr->SetPosition(Camera::CalculateUIPosition(Vector2(30.0f, 50.0f)));
		mana->SetMp(player->GetMp());

		//HP ������� �����ֱ�
		for (int i = 0; i < hp_container.size(); i++)
		{
			if (i > player->GetHp() - 1)
			{
				hp_container[i]->SetState(GameObject::eState::Pause);
			}
		}

		


		//�Է� ���� �� ũ�⿡ ���� ī�޶� ������ ���� ����
		Transform* player_tr = player->GetComponent<Transform>();
		Vector2 cur_pos = player_tr->GetPosition();
		if ((cur_pos.x > pos.x && cur_pos.y > pos.y) ||(cur_pos.x < -pos.x / 2 && cur_pos.y < pos.y /2))
			Camera::SetTarget(nullptr);
		else
			Camera::SetTarget(player);
	}
	void PlayerTemplate::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}