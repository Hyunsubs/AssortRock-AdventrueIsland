#include "Input.h"

namespace input
{
	//스태틱 변수는 꼭 외부에서 초기화 해주어야 한다.
	std::vector<Input::Key> Input::mKeys = {};

	int ASCII[(int)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};


	void Input::Initialize()
	{
		for (int i = 0; i < (int)eKeyCode::End; i++)
		{
			Key key = {};
			key.keyCode = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (int i = 0; i < (int)eKeyCode::End; i++)
		{
			
			//루프 돌며 아스키에 모든 키값들이 눌렸는지 확인
			//해당키가 눌려졌다.
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Pressed;
				else
					mKeys[i].state = eKeyState::Down;

				mKeys[i].bPressed = true;
			}
			

			else //해당키가 안눌려져 있다.
			{
				//이전 프레임에 눌려져 있었다.
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Up;
				else
					mKeys[i].state = eKeyState::None;

				mKeys[i].bPressed = false;
			}


		}


	}
}

