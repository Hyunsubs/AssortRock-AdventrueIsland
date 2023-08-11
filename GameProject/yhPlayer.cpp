#include "yhPlayer.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhAnimator.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhGameObject.h"
#include "yhCollider.h"
#include "yhPlayerSword.h"
#include "yhObject.h"
#include "yhSound.h"
#include "yhMana.h"
#include "yhHpInterface.h"
#include "yhPlayerShield.h"
#include "yhTexture.h"
#include "yhGrass.h"



#define PLAYER_SPEED 200.0f

namespace yh
{
	Player::Player()
		:state(PlayerState::Idle),
		direction(Directions::Backward),
		hp(3),
		mp(0),
		max_hp(3),
		rupee(0),
		bomb(0),
		arrow(0),
		is_dead(false),
		is_Wall(false),
		is_Bridge(false),
		stair_time(2.0f),
		is_Down(true),
		grass(nullptr)
	{
		//플레이어 위치 정보
		Vector2 myPos = GetComponent<Transform>()->GetPosition();

		//검 인스턴스화
		sword = object::Instantiate<PlayerSword>(eLayerType::Sword, myPos);

		//풀 인스턴스화 후 일단 pause
		grass = object::Instantiate<Grass>(eLayerType::Player, myPos);
		grass->SetState(GameObject::eState::Pause);

		//플레이어 애니메이션 세팅 이동관련
		std::wstring player_path = PLAYER_PATH;
		 Texture* image = Resources::Load<Texture>(L"LinkImage"
			, player_path + L"Link_Movement\\link_main.bmp");;

		at = AddComponent<Animator>();
		at->CreateAnimation(L"LinkForward", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 9, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleDown", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkBackward", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 9, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleUp", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 11, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkIdleRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 1, Vector2::Zero, 0.05f);
		image = Resources::Load<Texture>(L"LinkLeftSide", player_path + L"Link_Movement\\leftside.bmp");
		at->CreateAnimation(L"LinkIdleLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 1, Vector2::Zero, 0.05f);
		at->CreateAnimation(L"LinkLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 12, Vector2::Zero, 0.05f);
		at->SetAffectedCamera(true);
		at->SetScale(Vector2(2.0f, 2.0f));

		//링크 공격관련 애니메이션
		at->CreateAnimationFolder(L"LinkAttackRight", player_path + L"Link_Movement\\Link_Attack_Right", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackLeft", player_path + L"Link_Movement\\Link_Attack_Left", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackBackward", player_path + L"Link_Movement\\Link_Attack_Backward", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkAttackForward", player_path + L"Link_Movement\\Link_Attack_Forward", Vector2::Zero, 0.02f);
		at->CreateAnimationFolder(L"LinkChargeAttackBackward", player_path + L"Link_Movement\\Link_Charge_Attack_Backward",Vector2::Zero, 0.03f);
		//링크 사망
		at->CreateAnimationFolder(L"LinkDeath", player_path + L"Link_Death", Vector2::Zero, 0.3f);
		//링크 장애물 옮기기
		at->CreateAnimationFolder(L"LinkCarrying", player_path + L"Link_Carrying", Vector2::Zero, 0.2f);
		//링크 낙사
		at->CreateAnimationFolder(L"LinkFalling", player_path + L"Link_Falling", Vector2::Zero, 0.2f);

		//링크 구조물 던지기 준비동작
		at->CreateAnimationFolder(L"LinkThrowingForwardStart", player_path + L"Link_Throwing\\Link_Throwing_Forward_Start");
		at->CreateAnimationFolder(L"LinkThrowingBackwardStart", player_path + L"Link_Throwing\\Link_Throwing_Backward_Start");
		at->CreateAnimationFolder(L"LinkThrowingLeftStart", player_path + L"Link_Throwing\\Link_Throwing_Left_Start");
		at->CreateAnimationFolder(L"LinkThrowingRightStart", player_path + L"Link_Throwing\\Link_Throwing_Right_Start");

		//링크 구조물 들고 있을때
		at->CreateAnimationFolder(L"LinkThrowingForward", player_path + L"Link_Throwing\\Link_Throwing_Forward");
		at->CreateAnimationFolder(L"LinkThrowingBackward", player_path + L"Link_Throwing\\Link_Throwing_Backward");
		at->CreateAnimationFolder(L"LinkThrowingLeft", player_path + L"Link_Throwing\\Link_Throwing_Left");
		at->CreateAnimationFolder(L"LinkThrowingRight", player_path + L"Link_Throwing\\Link_Throwing_Right");

		//링크 구조물 들고 있을때 정지
		at->CreateAnimationFolder(L"LinkThrowingForwardIdle", player_path + L"Link_Throwing\\Link_Throwing_Forward_Idle");
		at->CreateAnimationFolder(L"LinkThrowingBackwardIdle", player_path + L"Link_Throwing\\Link_Throwing_Backward_Idle");
		at->CreateAnimationFolder(L"LinkThrowingLeftIdle", player_path + L"Link_Throwing\\Link_Throwing_Left_Idle");
		at->CreateAnimationFolder(L"LinkThrowingRightIdle", player_path + L"Link_Throwing\\Link_Throwing_Right_Idle");

		//링크 계단 아래 지나갈때 아무것도 없는 이미지
		at->CreateAnimationFolder(L"LinkDownBridgeAnim", player_path + L"Link_DownBridge");

		//떨어질때 컷신 용
		at->CreateAnimationFolder(L"LinkFallingCutScene", player_path + L"Link_Falling_Cut");

		//링크 맞았을때
		at->CreateAnimationFolder(L"LinkHitForward", player_path + L"Link_Hit\\Forward", Vector2::Zero, 0.3f);
		at->CreateAnimationFolder(L"LinkHitBackward", player_path + L"Link_Hit\\Backward", Vector2::Zero, 0.3f);
		at->CreateAnimationFolder(L"LinkHitLeft", player_path + L"Link_Hit\\Left", Vector2::Zero, 0.3f);
		at->CreateAnimationFolder(L"LinkHitRight", player_path + L"Link_Hit\\Right", Vector2::Zero, 0.3f);


		//충돌판정용 Collider
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(40.0f, 30.0f));



		//링크 효과음
		AttackSound = Resources::Load<Sound>(L"BasicAttack", L"..\\Resources\\sound\\Attack\\Sword1.wav");
		Alert = Resources::Load<Sound>(L"AlertSound", L"..\\Resources\\sound\\State\\LowHP.wav");
		//처음 시작했을때
		at->PlayAnimation(L"LinkIdleDown");
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		
	}




	void Player::Update()
	{
		GameObject::Update();
		sword->SetThrowing(is_Throwing);
		if (rupee >= 255)
			rupee = 255;
		if (bomb >= 20)
			bomb = 20;
		if (arrow >= 20)
			arrow = 20;
		if (is_Bridge)
			state = PlayerState::DownBridge;


		CheckPixel(PixelTexture, map_size);

		if (is_dead)
			return;
		Vector2 my_pos = GetComponent<Transform>()->GetPosition();
		Transform* tr = sword->GetComponent<Transform>();
		tr->SetPosition(my_pos);
		tr = grass->GetComponent<Transform>();
		tr->SetPosition(Vector2(my_pos.x, my_pos.y - 32.0f));

		DirectionSet();

		switch (state)
		{
		case yh::Player::PlayerState::Idle:
			Idle();
			break;
		case yh::Player::PlayerState::Move:
			Move();
			break;
		case yh::Player::PlayerState::Attack:
			Attack();
			break;
		case yh::Player::PlayerState::Death:
			Death();
			break;
		case yh::Player::PlayerState::Falling:
			Falling();
			break;
		case yh::Player::PlayerState::Carrying:
			Carrying();
			break;
		case yh::Player::PlayerState::DownBridge:
			DownBridge();
			break;
		case yh::Player::PlayerState::In_Stair:
			In_Stair();
			break;
		case yh::Player::PlayerState::Map:
			Map();
			break;
		case yh::Player::PlayerState::Charge:
			Charge();
			break;
		case yh::Player::PlayerState::Throwing:
			Throwing();
			break;
		case yh::Player::PlayerState::Fall_Cut_Scene:
			FallCutScene();
			break;
		case yh::Player::PlayerState::Hit:
			Hit();
			break;
		case yh::Player::PlayerState::Ui:
			Ui();
			break;
		}

		//shield->SetDirection(direction);
		
		

		if (hp <= 0)
		{
			Death();
			is_dead = true;
		}

		
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Player::OnCollisionEnter(Collider* other)
	{
		
	}

	void Player::OnCollisionStay(Collider* other)
	{
	}

	void Player::OnCollisionExit(Collider* other)
	{
	}


	void Player::Idle()
	{
		Animator* anim = GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::W))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingBackward", true);
			}
			else
			{
				anim->PlayAnimation(L"LinkBackward", true);
			}
			state = PlayerState::Move;
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingLeft", true);
			}
			else
			{
				anim->PlayAnimation(L"LinkLeft", true);
			}
			state = PlayerState::Move;
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingForward", true);
			}

			else
			{
				anim->PlayAnimation(L"LinkForward", true);
			}

			state = PlayerState::Move;
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingRight", true);
			}
			else
			{
				anim->PlayAnimation(L"LinkRight", true);
			}
			state = PlayerState::Move;
			direction = Directions::Right;
		}

		if (Input::GetKeyDown(eKeyCode::J) && !is_Throwing)
		{
			state = PlayerState::Attack;
			AttackSound->Play(false);
		}


		if (Input::GetKey(eKeyCode::L))
		{
			rupee++;
			mp--;
		}


		if (Input::GetKeyDown(eKeyCode::K))
		{
			state = PlayerState::Throwing;
				
		}


	}

	void Player::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		MoveFunc();

		if (Input::GetKeyUp(eKeyCode::W))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingBackwardIdle", false);
			}

			else
			{
				anim->PlayAnimation(L"LinkIdleUp", false);
			}

			direction = Directions::Forward;
			state = PlayerState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingLeftIdle", false);
			}
			else
			{
				anim->PlayAnimation(L"LinkIdleLeft", false);
			}
			
			direction = Directions::Left;
			state = PlayerState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingForwardIdle", false);
			}
			else
			{
				anim->PlayAnimation(L"LinkIdleDown", false);
			}
			direction = Directions::Backward;
			state = PlayerState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			if (is_Throwing)
			{
				anim->PlayAnimation(L"LinkThrowingRightIdle", false);
			}
			else
			{
				anim->PlayAnimation(L"LinkIdleRight", false);
			}
			direction = Directions::Right;
			state = PlayerState::Idle;
		}
		


	}

	void Player::MoveFunc()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (!is_Wall)
		{
			if (Input::GetKey(eKeyCode::W))
			{
				pos.y -= PLAYER_SPEED * Time::DeltaTime();
				direction = Directions::Forward;
			}
			if (Input::GetKey(eKeyCode::A))
			{
				pos.x -= PLAYER_SPEED * Time::DeltaTime();
				direction = Directions::Right;
			}
			if (Input::GetKey(eKeyCode::S))
			{
				pos.y += PLAYER_SPEED * Time::DeltaTime();
				direction = Directions::Backward;
			}
			if (Input::GetKey(eKeyCode::D))
			{
				pos.x += PLAYER_SPEED * Time::DeltaTime();
				direction = Directions::Right;
			}
			tr->SetPosition(pos);
		}
	}

	void Player::Attack()
	{
		Animator* anim = GetComponent<Animator>();
		switch (direction)
		{
		case yh::Directions::Forward:
			anim->PlayAnimation(L"LinkAttackForward", false);
			direction = Directions::Forward;
			break;
		case yh::Directions::Backward:
			anim->PlayAnimation(L"LinkAttackBackward", false);
			direction = Directions::Backward;
			break;
		case yh::Directions::Left:
			anim->PlayAnimation(L"LinkAttackLeft", false);
			direction = Directions::Left;
			break;
		case yh::Directions::Right:
			anim->PlayAnimation(L"LinkAttackRight", false);
			direction = Directions::Right;
			break;
		default:
			break;
		}

		state = PlayerState::Idle;


		if (Input::GetKeyDown(eKeyCode::J))
		{
			state = PlayerState::Charge;
		}
		
	}

	void Player::Death()
	{
		Destroy(sword);
		at->PlayAnimation(L"LinkDeath", false);
	}

	void Player::Map()
	{
		
	}

	void Player::Carrying()
	{
		Animator* anim = GetComponent<Animator>();
		if (anim->IsActiveAnimationComplete())
			state = PlayerState::Idle;
	}

	void Player::Throwing()
	{
		Animator* anim = GetComponent<Animator>();
		Transform* grass_tr = grass->GetComponent<Transform>();
		is_Throwing = !is_Throwing;
		if (!is_Throwing)
		{
			Transform* player_tr = GetComponent<Transform>();
			Vector2 my_pos = player_tr->GetPosition();
			if (grass->GetState() == eState::Active)
			{
				grass->SetState(eState::Pause);
				Grass* new_grass = object::Instantiate<Grass>(eLayerType::Grass, Vector2(my_pos.x, my_pos.y - 32.0f));
				new_grass->SetDirection(GetDirection());
				new_grass->SetGrassState(grass_state::Flying);
			}

			Vector2 myPos = GetComponent<Transform>()->GetPosition();
			shield = object::Instantiate<PlayerShield>(eLayerType::Shield, myPos);
			switch (direction)
			{
			case yh::Directions::UpLeft:
				direction = Directions::Forward;
			case yh::Directions::UpRight:
				direction = Directions::Forward;
			case yh::Directions::Forward:
				anim->PlayAnimation(L"LinkIdleUp");
				break;
			case yh::Directions::DownLeft:
				direction = Directions::Backward;
			case yh::Directions::DownRight:
				direction = Directions::Backward;
			case yh::Directions::Backward:
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Left:
				anim->PlayAnimation(L"LinkIdleLeft");
				break;
			case yh::Directions::Right:
				anim->PlayAnimation(L"LinkIdleRight");
				break;
			default:
				break;
			}
		}
		else
		{


			switch (direction)
			{
			case yh::Directions::Forward:
				anim->PlayAnimation(L"LinkThrowingBackwardStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::Backward:
				anim->PlayAnimation(L"LinkThrowingForwardStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::Left:
				anim->PlayAnimation(L"LinkThrowingLeftStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::Right:
				anim->PlayAnimation(L"LinkThrowingRightStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::DownRight:
				anim->PlayAnimation(L"LinkThrowingBackwardStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::DownLeft:
				anim->PlayAnimation(L"LinkThrowingBackwardStart", false);
				is_Throwing = true;
				break;
			case yh::Directions::UpRight:
				anim->PlayAnimation(L"LinkThrowingForwardStart", false);
				is_Throwing = true;
				break;
				case yh::Directions::UpLeft:
				anim->PlayAnimation(L"LinkThrowingForwardStart", false);
				is_Throwing = true;
				break;
			default:
				break;
			}
		}
		state = PlayerState::Idle;
	
	
		
	}

	void Player::Charge()
	{
		Animator* anim = GetComponent<Animator>();
		if (Input::GetKeyDown(eKeyCode::J))
		{
			anim->PlayAnimation(L"LinkChargeAttackBackward", false);
		}

		if (Input::GetKeyUp(eKeyCode::J))
		{
			anim->PlayAnimation(L"LinkChargeAttackBackward", false);
			state = PlayerState::Idle;
		}

	}

	void Player::Hit()
	{
		Animator* anim = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Vector2 my_pos = tr->GetPosition();
		if (!(anim->IsActiveAnimationComplete()))
		{
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				my_pos.y += 200.0f * Time::DeltaTime();
				break;
			case yh::enums::Directions::Backward:
				my_pos.y -= 200.0f * Time::DeltaTime();
				break;
			case yh::enums::Directions::Left:
				my_pos.x += 200.0f * Time::DeltaTime();
				break;
			case yh::enums::Directions::Right:
				my_pos.x -= 200.0f * Time::DeltaTime();
				break;
			default:
				break;
			}
			tr->SetPosition(my_pos);
		}
		else if (anim->IsActiveAnimationComplete())
		{
			state = PlayerState::Idle;
		}
	}

	void Player::DownBridge()
	{
		if (is_Bridge)
		{
			at->PlayAnimation(L"LinkDownBridgeAnim", false);
			MoveFunc();
		}

		else
		{
			state = PlayerState::Idle;
		}
	}

	void Player::DirectionSet()
	{
		if (Input::GetKey(eKeyCode::W))
		{
			direction = Directions::Forward;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			direction = Directions::Left;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			direction = Directions::Backward;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			direction = Directions::Right;
		}
		if (Input::GetKey(eKeyCode::D) && Input::GetKey(eKeyCode::W))
		{
			direction = Directions::UpRight;
		}
		if (Input::GetKey(eKeyCode::A) && Input::GetKey(eKeyCode::W))
		{
			direction = Directions::UpLeft;
		}
		if (Input::GetKey(eKeyCode::S) && Input::GetKey(eKeyCode::A))
		{
			direction = Directions::DownRight;
		}
		if (Input::GetKey(eKeyCode::S) && Input::GetKey(eKeyCode::D))
		{
			direction = Directions::DownLeft;
		}


	}

	void Player::CheckPixel(Texture* pixel_texture, Vector2 map_size)
	{
		if (pixel_texture == nullptr)
			return;
		std::vector<COLORREF> rgbs;
		Transform* my_tr = GetComponent<Transform>();
		COLORREF down_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x, my_tr->GetPosition().y + map_size.y + 13);
		COLORREF up_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x, my_tr->GetPosition().y + map_size.y - 13);
		COLORREF left_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x - 13, my_tr->GetPosition().y + map_size.y);
		COLORREF right_color = pixel_texture->GetTexturePixel(my_tr->GetPosition().x + map_size.x + 13, my_tr->GetPosition().y + map_size.y);

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

	void Player::Falling()
	{
		Animator* anim = GetComponent<Animator>();
		if (anim->IsActiveAnimationComplete())
		{
			hp--;
			state = PlayerState::Idle;
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			switch (direction)
			{
			case yh::Directions::Forward:
				pos.y += 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Backward:
				pos.y -= 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Left:
				pos.x += 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			case yh::Directions::Right:
				pos.x -= 40.0f;
				tr->SetPosition(pos);
				anim->PlayAnimation(L"LinkIdleDown");
				break;
			default:
				break;
			}

		}

	}

	void Player::FallCutScene()
	{
		Transform* player_tr = GetComponent<Transform>();
		Vector2 player_pos = player_tr->GetPosition();
		while (player_pos.y >= 0.0f)
		{
			player_pos.y -= 100.0f * Time::DeltaTime();
			player_tr->SetPosition(player_pos);
		}
		state = PlayerState::Idle;
	}

	void Player::In_Stair()
	{
		stair_time -= Time::DeltaTime();

		Transform* player_tr = GetComponent<Transform>();
		Vector2 player_pos = player_tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		if (stair_time <= 0.0f)
		{
			is_Down = !is_Down;
			state = PlayerState::Idle;
			stair_time = 2.0f;
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				anim->PlayAnimation(L"LinkIdleUp", false);
				break;
			case yh::enums::Directions::Backward:
				anim->PlayAnimation(L"LinkIdleDown", false);
				break;
			default:
				break;
			}
		}

		else
		{
			if (is_Down)
			{
				player_pos.y -= 50.0f * Time::DeltaTime();

			}
			if (!is_Down)
			{
				player_pos.y += 50.0f * Time::DeltaTime();

			}



			player_tr->SetPosition(player_pos);
		}
			
	}

	void Player::Talking()
	{
	}

	void Player::Ui()
	{
	}

	




}


