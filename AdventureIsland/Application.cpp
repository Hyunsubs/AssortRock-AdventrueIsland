#include "Application.h"
#include "Input.h"

using namespace key_logic;

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

	if (Input::GetKey(eKeyCode::W))
	{
		mPlayerPos.y -= 0.01f;
	}

	if (Input::GetKey(eKeyCode::A))
	{
		mPlayerPos.x -= 0.01f;
	}


	if (Input::GetKey(eKeyCode::S))
	{
		mPlayerPos.y += 0.01f;
	}


	if (Input::GetKey(eKeyCode::D))
	{
		mPlayerPos.x += 0.01f;
	}

	
	
}

void Application::Render()
{
	Ellipse(mHdc, 100 + mPlayerPos.x, 100 + mPlayerPos.y, 200 +mPlayerPos.x, 200 + mPlayerPos.y);
}
