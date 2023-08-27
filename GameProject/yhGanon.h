#pragma once
#include "yhGameObject.h"

namespace yh
{
	enum class FirstPhase
	{
		Throwing,
		PhantomMove,
		Spinning,
		None,
	};

	enum class SecondPhase
	{
		PhantomMove,
		FireSpin,
		BatsFollowing,
		None,
	};

	enum class ThirdPhase
	{
		Death,
		None,
	};

	enum class CurrentPhase
	{
		First,
		Second,
		Third,
		FirstTalking,
		SecondTalking
	};


	class Ganon : public GameObject
	{
	public:
		Ganon();
		virtual ~Ganon();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayerPos(Vector2 input) { PlayerPos = input; }

		void ThrowingFirst();
		void PhantomMoveFirst(int rand_num);
		void SpinningFirst();

		void FirstTalking();
		void SecondTalking();

		void PhantomMoveSecond(int rand_num);
		void FireSpinSecond();
		void BatsFollowingSecond();

		void Death();

		CurrentPhase GetCurPhase() { return cur_phase; }

		int GetFirstHp() { return first_hp; }
		int GetSecondHp() { return second_hp; }

		void SetFirstHp(int first) { first_hp = first; }
		void SetSecondHp(int second) { second_hp = second; }

		void GetPlayer(class Player* input) { player = input; }
		
	private:
		CurrentPhase cur_phase;
		FirstPhase first_phase;
		SecondPhase second_phase;
		ThirdPhase third_phase;

		class Transform* tr;
		class Animator* anim;
		class Collider* col;

		//가논이 던지는 삼지창
		class GanonTrident* trident;


		//가논 방향
		Directions direct;


		//위치 관련
		Vector2 PlayerPos; //플레이어 추적용
		Vector2 FirstPhasePos[6]; //1페이즈 랜덤하게 움직일 위치 PhantomMove때 사용
		Vector2 SecondPhasepPos[10]; //2페이즈 랜덤하게 움직일 위치
		Vector2 ThirdPhasePos[10]; // 3페이즈 랜덤하게 움직일 위치

		//1페이즈 실행 시간 관련
		float throwing_time;
		float phantom_move_time;
		float spinning_time;

		//알파값
		float cur_alpha;

		//위치 정할 인덱스
		int rand_num;


		//대사 출력용 
		int idx;
		vector<class AsciiRender*> first_dialogue;
		vector<class AsciiRender*> second_dialogue;
		class AsciiRender* ascii;

		int first_hp;
		int second_hp;
		int third_hp;

		bool second_on;
		bool third_on;


		//플레이어 조작
		class Player* player;

		float make_bats;
		int max_bats;

		class Sound* talking_sound;
		class Sound* fight_sound;
		class Sound* die_sound;

		bool talking_sound_played;
	};
}


