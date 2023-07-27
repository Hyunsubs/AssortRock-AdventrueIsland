#pragma once
#include "CommonInclude.h"

namespace yh 
{
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Up, Down, Left, Right,
		MouseLeft, MouseRight, MouseWheel,
		Space,
		End,
	};

	enum class eKeyState
	{
		Down,
		Up,
		Pressed,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode code;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();

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
		__forceinline static math::Vector2 GetMousePosition()
		{
			return mMousePosition;
		}

	private:
		static std::vector<Key> mKeys;
		static math::Vector2 mMousePosition;
	};
}


