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
#include "yhNumber.h"
#include "yhCollisionManager.h"

namespace yh
{


	PlayerTemplate::PlayerTemplate() :
		  mana(nullptr)
		, manapoints(nullptr)
		, player(nullptr)
		, sword(nullptr)
		, arrow(nullptr)
		, bomb(nullptr)
		, cur_item(nullptr)
		, life(nullptr)
		, rupee_ui(nullptr)
		, rupee_first_digit(nullptr)
		, rupee_second_digit(nullptr)
		, rupee_third_digit(nullptr)
		, bomb_first_digit(nullptr)
		, bomb_second_digit(nullptr)
		, arrow_first_digit(nullptr)
		, arrow_second_digit(nullptr)
										
	{
		
	}
	PlayerTemplate::~PlayerTemplate()
	{
	}
	void PlayerTemplate::Initialize()
	{
		//화면 변경가능한 씬체인저
		object::Instantiate<SceneChanger>(eLayerType::Background);
		//플레이어 세팅
		player = object::Instantiate<Player>(eLayerType::Player, Vector2(0.0f, 0.0f));
		//마나 UI
		mana = object::Instantiate<Mana>(eLayerType::UI);
		//life 글씨
		life = object::Instantiate<LifeUI>(eLayerType::UI);
		life->SetState(GameObject::eState::Active);
		//화살 갯수 UI
		arrow = object::Instantiate<Arrow>(eLayerType::UI);
		arrow->SetState(GameObject::eState::Active);
		//폭탄 갯수 UI
		bomb = object::Instantiate<Bomb>(eLayerType::UI);
		bomb->SetState(GameObject::eState::Active);
		//루피 갯수 UI
		rupee_ui = object::Instantiate<RupeeUI>(eLayerType::UI);
		rupee_ui->SetState(GameObject::eState::Active);
		//현재 아이템 UI
		cur_item = object::Instantiate<CurItem>(eLayerType::UI);
		cur_item->SetState(GameObject::eState::Active);

		//루피 갯수 숫자
		rupee_first_digit = object::Instantiate<Number>(eLayerType::UI);
		rupee_second_digit = object::Instantiate<Number>(eLayerType::UI);
		rupee_third_digit = object::Instantiate<Number>(eLayerType::UI);
		//폭탄 갯수 숫자
		bomb_first_digit = object::Instantiate<Number>(eLayerType::UI);
		bomb_second_digit = object::Instantiate<Number>(eLayerType::UI);
		//화살 갯수 숫자
		arrow_first_digit = object::Instantiate<Number>(eLayerType::UI);
		arrow_second_digit = object::Instantiate<Number>(eLayerType::UI);

		//체력UI 인스턴스화 후 벡터에 추가
		for (int i = 0; i < player->GetMaxHp(); i++)
		{
			HpInterface* hp = object::Instantiate<HpInterface>(eLayerType::UI);
			hp_container.push_back(hp);
		}


		//층돌 체크 설정
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Obstacle, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::PitFall, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::Sword, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Items, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::PitFall, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MapChanger, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Stair, true);
	}

	void PlayerTemplate::Update(Vector2 size)
	{

		Scene::Update();

		for (int i = 0; i < player->GetHp(); i++)
		{
			if (hp_container[i]->GetState() == GameObject::eState::Dead || hp_container[i]->GetState() == GameObject::eState::Pause)
			{
				hp_container[i]->SetState(GameObject::eState::Active);
			}

			Transform* tr = hp_container[i]->GetComponent<Transform>();
			tr->SetPosition(Camera::CalculateUIPosition(Vector2(340.0f + i * 15, 70.0f)));
		}

		//라이프 글자 띄우기
		Transform* life_tr = life->GetComponent<Transform>();
		life_tr->SetPosition(Camera::CalculateUIPosition(Vector2(400.0f, 50.0f)));

		//화살 UI 띄우기
		int arrow_amount = player->GetArrow();
		arrow_first_digit->SetNumber(arrow_amount / 10);
		arrow_second_digit->SetNumber(arrow_amount % 10);
		Transform* arrow_tr = arrow->GetComponent<Transform>();
		arrow_tr->SetPosition(Camera::CalculateUIPosition(Vector2(240.0f, 60.0f)));
		arrow_tr = arrow_first_digit->GetComponent<Transform>();
		arrow_tr->SetPosition(Camera::CalculateUIPosition(Vector2(230.0f, 80.0f)));
		arrow_tr = arrow_second_digit->GetComponent<Transform>();
		arrow_tr->SetPosition(Camera::CalculateUIPosition(Vector2(245.0f, 80.0f)));
		//폭탄 UI 띄우기
		int bomb_amount = player->GetBomb();
		bomb_first_digit->SetNumber(bomb_amount / 10);
		bomb_second_digit->SetNumber(bomb_amount % 10);
		Transform* bomb_tr = bomb->GetComponent<Transform>();
		bomb_tr->SetPosition(Camera::CalculateUIPosition(Vector2(190.0f, 60.0f)));
		bomb_tr = bomb_first_digit->GetComponent<Transform>();
		bomb_tr->SetPosition(Camera::CalculateUIPosition(Vector2(180.0f, 80.0f)));
		bomb_tr = bomb_second_digit->GetComponent<Transform>();
		bomb_tr->SetPosition(Camera::CalculateUIPosition(Vector2(195.0f, 80.0f)));
		//루피 UI 띄우기
		int rupee_amount = player->GetRupee();
		rupee_first_digit->SetNumber(rupee_amount / 100);
		rupee_second_digit->SetNumber(rupee_amount % 100 / 10);
		rupee_third_digit->SetNumber(rupee_amount % 10);
		Transform * rupee_tr = rupee_ui->GetComponent<Transform>();
		rupee_tr->SetPosition(Camera::CalculateUIPosition(Vector2(140.0f, 60.0f)));
		rupee_tr = rupee_first_digit->GetComponent<Transform>();
		rupee_tr->SetPosition(Camera::CalculateUIPosition(Vector2(125.0f, 80.0f)));
		rupee_tr = rupee_second_digit->GetComponent<Transform>();
		rupee_tr->SetPosition(Camera::CalculateUIPosition(Vector2(140.0f, 80.0f)));
		rupee_tr = rupee_third_digit->GetComponent<Transform>();
		rupee_tr->SetPosition(Camera::CalculateUIPosition(Vector2(155.0f, 80.0f)));
		//현재 아이템 UI 띄우기
		Transform* cur_item_tr = cur_item->GetComponent<Transform>();
		cur_item_tr->SetPosition(Camera::CalculateUIPosition(Vector2(67.0f,30.0f)));

		//MP 인터페이스
		Transform* mana_tr = mana->GetComponent<Transform>();
		mana_tr->SetPosition(Camera::CalculateUIPosition(Vector2(30.0f, 50.0f)));
		mana->SetMp(player->GetMp());

		//HP 닳았을때 지워주기
		for (int i = 0; i < hp_container.size(); i++)
		{
			if (i > player->GetHp() - 1)
			{
				hp_container[i]->SetState(GameObject::eState::Pause);
			}
		}


		float map_left_end_x = map_pos.x - ((size.x * map_scale.x) / 2.0f);
		float map_up_end_y = map_pos.y - ((size.y * map_scale.y) / 2.0f);
		float map_right_end_x = map_pos.x + ((size.x * map_scale.x) / 2.0f);
		float map_down_end_y = map_pos.y + ((size.y * map_scale.y) / 2.0f);

		float allow_left_x = map_left_end_x + 256.0f;
		float allow_right_x = map_right_end_x - 256.0f;
		float allow_up_y = map_up_end_y + 256.0f;
		float allow_down_y = map_down_end_y - 256.0f;

		Vector2 player_pos = player->GetComponent<Transform>()->GetPosition();

		//카메라가 완전 바운더리 내에 있을때
		if (player_pos.x > allow_left_x && player_pos.x < allow_right_x && player_pos.y < allow_down_y && player_pos.y > allow_up_y)
		{
			Camera::SetTarget(player);
		}
		//카메라가 왼쪽 아래 모두 바운더리 초과한 상황
		else if (player_pos.x < allow_left_x && player_pos.y > allow_down_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(allow_left_x, allow_down_y));
		}
		//카메라가 왼쪽 바운더리 초과 상하 바운더리 내에 있을때
		else if (player_pos.x < allow_left_x && player_pos.y && player_pos.y < allow_down_y && player_pos.y > allow_up_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(allow_left_x, player_pos.y));
		}
		//카메라가 오른쪽 바운더리 초과 상하 바운더리 내에 있을때
		else if (player_pos.x > allow_right_x && player_pos.y && player_pos.y < allow_down_y && player_pos.y > allow_up_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(allow_right_x, player_pos.y));
		}
		//카메라가 아래 바운더리 초과 좌우 바운더리 내에 있을때
		else if (player_pos.x < allow_right_x && player_pos.x > allow_left_x && player_pos.y > allow_down_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(player_pos.x, allow_down_y));
		}
		//카메라가 오른쪽 아래 모두 바운더리 초과한 상황
		else if (player_pos.x > allow_right_x && player_pos.y > allow_down_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(allow_right_x, allow_down_y));
		}
		//카메라가 위 바운더리 초과 좌우 바운더리 내에 있을때
		else if (player_pos.x < allow_right_x && player_pos.x > allow_left_x && player_pos.y < allow_up_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(player_pos.x, allow_up_y));
		}
		//카메라가 오른쪽 위 모두 바운더리 초과한 상황
		else if (player_pos.x > allow_right_x && player_pos.y < allow_up_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(allow_right_x, allow_up_y));
		}
		//카메라가 왼쪽 위 모두 바운더리 초과한 상황
		else if (player_pos.x < allow_left_x && player_pos.y < allow_up_y)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookPosition(Vector2(allow_left_x, allow_up_y));
		}
		else
			Camera::SetTarget(nullptr);

		if (Input::GetKey(eKeyCode::R))
		{
			HpInterface* hp = object::Instantiate<HpInterface>(eLayerType::UI);
			hp_container.push_back(hp);
			int max_hp = player->GetMaxHp();
			max_hp++;
			int cur_hp = player->GetHp();
			cur_hp++;

			player->SetMaxHp(max_hp);
			player->SetHp(cur_hp);
		}

	}




	void PlayerTemplate::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//프레임 표시
		wchar_t szFloat[50] = {};
		Vector2 Player_pos = player->GetComponent<Transform>()->GetPosition();
		swprintf_s(szFloat, 50, L"PlayerPosition : x: %f , y: %f", Player_pos.x, Player_pos.y);
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 10, szFloat, strLen);
	}

	Vector2 PlayerTemplate::GetPlayerPos()
	{
		return player->GetComponent<Transform>()->GetPosition(); 
	}

	void PlayerTemplate::SetPlayerPos(Vector2 pos)
	{
		player->GetComponent<Transform>()->SetPosition(pos); 
	}

	void PlayerTemplate::Save(std::string path)
	{
		std::ofstream ofs(path, std::ios::out | std::ios::trunc);
		if (ofs.fail())
		{
			std::cout << "Error!" << std::endl;
		}
		ofs << std::to_string(player->GetRupee());
		ofs << "\n";
		ofs << std::to_string(player->GetBomb());
		ofs << "\n";
		ofs << std::to_string(player->GetArrow());
		ofs << "\n";
		ofs << std::to_string(player->GetHp());
		ofs << "\n";
		
		ofs.close();
		
	}

	void PlayerTemplate::SavePosition()
	{
		std::ofstream ofs("..\\Resources\\SaveData\\PlayerPosition.txt", std::ios::out | std::ios::trunc);
		Vector2 player_pos = player->GetComponent<Transform>()->GetPosition();
		if (ofs.fail())
		{
			std::cout << "Error!" << std::endl;
		}
		ofs << player_pos.x;
		ofs << "\n";
		ofs << player_pos.y;
		ofs << "\n";

		ofs.close();

	}

	void PlayerTemplate::Load(std::string path)
	{
		std::ifstream ifs;
		ifs.open(path, std::ios::in);
		if (!ifs)
		{
			std::cout << "Error!" << std::endl;
		}


		std::string line;
		int i = 0;
		while (i <= 3)
		{
			getline(ifs, line);
			switch (i)
			{
			case 0:
				player->SetRupee(std::stoi(line));
				break;
			case 1:
				player->SetBomb(std::stoi(line));
				break;
			case 2:
				player->SetArrow(std::stoi(line));
				break;
			case 3:
				player->SetHp(std::stoi(line));
			default:
				break;
			}
			i++;
		}
		ifs.close();

	}

	void PlayerTemplate::LoadPosition()
	{
		float x_pos;
		float y_pos;
		std::ifstream ifs;
		ifs.open("..\\Resources\\SaveData\\PlayerPosition.txt", std::ios::in);
		if (!ifs)
		{
			std::cout << "Error!" << std::endl;
		}


		std::string line;
		int i = 0;
		while (i <= 1)
		{
			getline(ifs, line);
			switch (i)
			{
			case 0:
				x_pos = (std::stof(line));
				break;
			case 1:
				y_pos = (std::stof(line));
				break;
			}
			i++;
		}

		player->GetComponent<Transform>()->SetPosition(Vector2(x_pos, y_pos));

		ifs.close();

	}
}