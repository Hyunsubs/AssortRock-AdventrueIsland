#pragma once
#include "CommonInclude.h"

namespace input
{
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		End,
	};

	// 키의 상태
	enum class eKeyState
	{
		Down,
		Up,
		Pressed,
		None,
	};

	//enum 문제는 다른 enum을 만들고 열거이름을 똑같이 만들면
	//겹치는 문제가 생기지만
	//class로 만들면 겹치는 문제가 없다.

	class Input
	{
	public:
		struct Key
		{
			eKeyCode keyCode;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();

		//inline을 사용하면 속도에서 이점이 생긴다.
		//인라인 함수를 사용할땐 코드를 들여다보려 들어가는것이 아닌
		//코드 자체로 치환해 버린다.
		//인라인을 사용한다고 해서 모두 치환되는것이 아닌
		//비주얼 스튜디오 판단하에 작동된다.
		//자주 사용되는 함수는 인라인 처리 해주는 것이 속도면에서 좋다.

		__forceinline static bool GetKeyDown(eKeyCode code) 
		{ 
			return mKeys[(int)code].state == eKeyState::Down; 
		}
		__forceinline static bool GetKeyUp(eKeyCode code) 
		{
			return mKeys[(int)code].state == eKeyState::Up; 
		}
		__forceinline static bool GetKey(eKeyCode code) 
		{ 
			return mKeys[(int)code].state == eKeyState::Pressed; 
		}

		//forceinline을 붙이면 무조건 인라인 방식으로
		//치환된다.



		//static 클래스 안에서 전역변수 처럼 동작 함
		//정적변수
		//전역변수와 같이 선언시 데이터 영역에 들어감
	private:
		static std::vector<Key> mKeys;
	};
}


