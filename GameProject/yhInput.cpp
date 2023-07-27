#include "yhInput.h"
#include "yhApplication.h"

extern yh::Application application;

namespace yh 
{
	std::vector<Input::Key> Input::mKeys = {};
	math::Vector2 Input::mMousePosition = math::Vector2::Zero;

	int ASCII[(int)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
		VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
		VK_LBUTTON, VK_RBUTTON, MK_MBUTTON,
		VK_SPACE
	};

	void Input::Initialize()
	{
		for (size_t i = 0
			; i < (int)eKeyCode::End
			; i++)
		{
			Key key = {};
			key.code = (eKeyCode)i;
			key.state = eKeyState::None;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (size_t i = 0
			; i < (int)eKeyCode::End
			; i++)
		{
			// 해당키가 눌려졌다.
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				// 이전 프레임에도 눌려져 있었다.
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Pressed;
				else
					mKeys[i].state = eKeyState::Down;

				mKeys[i].bPressed = true;
			}
			else // 해당키가 안눌려져 있다.
			{
				// 이전프레임에 눌려져 있었다.
				if (mKeys[i].bPressed == true)
					mKeys[i].state = eKeyState::Up;
				else
					mKeys[i].state = eKeyState::None;

				mKeys[i].bPressed = false;
			}
		}

		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetHwnd(), &mousePos);
		mMousePosition.x = (float)mousePos.x;
		mMousePosition.y = (float)mousePos.y;
	}
}