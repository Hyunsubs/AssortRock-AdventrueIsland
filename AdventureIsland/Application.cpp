#include "Application.h"

key_logic::Application::Application()
	: mHwnd(NULL)
	, mHdc(NULL)
{
	
}

key_logic::Application::~Application()
{
}

void key_logic::Application::Initialize(HWND hwnd)
{
	mHwnd = hwnd;

	mHdc = GetDC(mHwnd);
}

void key_logic::Application::Run()
{
	Update();
	Render();
}

void key_logic::Application::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		mPlayerPos.x -= 0.01f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		mPlayerPos.x += 0.01f;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		mPlayerPos.y -= 0.01f;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		mPlayerPos.y += 0.01f;
	}

	
}

void key_logic::Application::Render()
{
	Ellipse(mHdc, 100 + mPlayerPos.x, 100 + mPlayerPos.y, 200 +mPlayerPos.x, 200 + mPlayerPos.y);
}
