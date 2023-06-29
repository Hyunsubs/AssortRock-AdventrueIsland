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

	// Ű�� ����
	enum class eKeyState
	{
		Down,
		Up,
		Pressed,
		None,
	};

	//enum ������ �ٸ� enum�� ����� �����̸��� �Ȱ��� �����
	//��ġ�� ������ ��������
	//class�� ����� ��ġ�� ������ ����.

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

		//inline�� ����ϸ� �ӵ����� ������ �����.
		//�ζ��� �Լ��� ����Ҷ� �ڵ带 �鿩�ٺ��� ���°��� �ƴ�
		//�ڵ� ��ü�� ġȯ�� ������.
		//�ζ����� ����Ѵٰ� �ؼ� ��� ġȯ�Ǵ°��� �ƴ�
		//���־� ��Ʃ��� �Ǵ��Ͽ� �۵��ȴ�.
		//���� ���Ǵ� �Լ��� �ζ��� ó�� ���ִ� ���� �ӵ��鿡�� ����.

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

		//forceinline�� ���̸� ������ �ζ��� �������
		//ġȯ�ȴ�.



		//static Ŭ���� �ȿ��� �������� ó�� ���� ��
		//��������
		//���������� ���� ����� ������ ������ ��
	private:
		static std::vector<Key> mKeys;
	};
}


