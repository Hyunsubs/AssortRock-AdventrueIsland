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
	if (check_time)
	{

		global_time++;
	}

	if (global_time == 5)
	{
		ball_vect.push_back(Ball());
		global_time = 0;
	}

	if (ball_vect.size() >= 10)
		ball_vect.pop_back();

	for (int i = 0; i < ball_vect.size(); i++)
	{
		ball_vect[i].Move(mHdc, ball_vect[i].rand_num);
		ball_vect[i].is_Wall();
	}
}
