#include "Application.h"
#include "Input.h"
#include "Time.h"
#include "Ball.h"

using namespace key_logic;
int global_time = 0;

std::vector<Ball> ball_vect = {};

Application::Application()
	: mHwnd(NULL)
	, mHdc(NULL)
{
	
}

Application::~Application()
{

}

void Application::Initialize(HWND hwnd)
{
	mHwnd = hwnd;
	mHdc = GetDC(mHwnd);

	mWidth = 1600;
	mHeight = 900;

	RECT rect = {0,0, mWidth, mHeight};
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//윈도우 해상도 동일한 비트맵 생성
	mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
	//새로 생성한 비트배을 가리키는 DC 생성
	mBackHdc = CreateCompatibleDC(mHdc);
	
	//새로 생성한 비트맵과 DC를 서로 연결
	HBITMAP defaultBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
	DeleteObject(defaultBitmap);

	input::Input::Initialize();
	key_logic::Time::Initialize();
	ball_vect.push_back(Ball()); //첫번째 공

}

void Application::Run()
{
	Update();
	Render();
}

void Application::Update()
{
	using namespace input;
	Input::Update();
	Time::Update();
	
}

void Application::Render()
{

	bool check_time = Time::Render(mHdc);

	Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);


	if (check_time)
	{

		global_time++;
	}

	if (global_time == 5)
	{
		if (ball_vect.size() > 10)
		{

		}
		else
		{
			ball_vect.push_back(Ball());
			global_time = 0;
		}
	}


	for (int i = 0; i < ball_vect.size(); i++)
	{
		ball_vect[i].Move(mBackHdc, ball_vect[i].rand_num);
		ball_vect[i].is_Wall();
	}
	BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
}
