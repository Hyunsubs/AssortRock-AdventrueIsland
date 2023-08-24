#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Player : public GameObject
	{
	public:
		enum class PlayerState
		{
			Idle,
			Move,
			Attack,
			Charge,
			Death,
			Map,
			Hit,
			DownBridge,
			In_Stair,
			Falling,
			ClutchState,
			Fall_Cut_Scene,
			Carrying,
			Inventory,
			Throwing,
			Talking,
			Step,
			Ui,
			End,
		};




		Player();
		virtual ~Player();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void Idle();
		void Move();
		void MoveFunc();
		void Attack();
		void Death();
		void Map();
		void Falling();
		void Ui();
		void Inventory_State();
		void Carrying();
		void Throwing();
		void Charge();
		void Hit();
		void DownBridge();
		void FallCutScene();
		void In_Stair();
		void Step();
		void Talking();
		void ClutchState();

		PlayerState GetState() { return state; }
		void SetState(PlayerState pstate) { state = pstate; }

		Directions GetDirection() { return direction; }
		void SetDirection(Directions direct) { direction = direct; }

		int GetMp() { return mp; }
		void SetMp(int num) { mp = num; }

		int GetHp() { return hp; }
		void SetHp(int num) { hp = num; }

		int GetMaxHp() { return max_hp; }
		void SetMaxHp(int input) { max_hp = input; }

		bool GetThrowing() { return is_Throwing; }
		void SetThrowing(bool input) { is_Throwing = input; }

		bool GetIsWall() { return is_Wall; }
		void SetIsWall(bool input) { is_Wall = input; }

		int GetRupee() { return rupee; }
		void SetRupee(int input) { rupee = input; }

		int GetBomb() { return bomb; }
		void SetBomb(int input) { bomb = input; }

		int GetArrow() { return arrow; }
		void SetArrow(int input) { arrow = input; }
	
		void DirectionSet();

		bool GetIsDead() { return is_dead; }

		bool GetBridge() { return is_Bridge; }
		void SetBridge(bool input) { is_Bridge = input; }

		bool GetIsDown() { return is_Down; }
		void SetIsDown(bool input) { is_Down = input; }

		void CheckPixel(class Texture* pixel_texture, Vector2 map_size);

		class PlayerGrass* GetGrass() { return grass; }
		
		bool GetIsHit() { return is_hit; }

		bool GetIsSword() { return is_sword; }
		void SetIsSword(bool input) { is_sword = input; }

		Vector2 map_size = Vector2::Zero;
		class Texture* PixelTexture;

	private:
		PlayerState state;
		Directions direction;
		std::vector<class HpInterface*> hp_container;
		

		class PlayerGrass* grass;
		class PlayerSword* sword;
		class PlayerShield* shield;
		class Mana* mana;
		class Sound* AttackSound;
		class Animator* at;
		class Sound* Alert;
		class Inventory* inven;
		class Transform* tr;
		class Boomerang* boomerang;
		class Clutch* clutch;


		//링크 상태
		bool is_dead;
		int max_hp;
		int hp;
		int mp;
		bool is_Throwing;
		bool is_Wall;
		bool is_Bridge;
		bool is_Down;

		//아이템 갯수
		int rupee;
		int bomb;
		int arrow;
		int cur_item;

		//아이템 획득 여부
		bool is_sword;
		bool is_hit;

		//계단 올라가는 시간
		float stair_time;
		//바닥 떨어지는 시간
		float step_time;

		//무적 피격시간
		float invincible_time;
	};
}


