#include "yhApplication.h"
#include "yhTime.h"
#include "yhInput.h"
#include "yhTitle.h"
#include "yhScene.h"
#include "yhSceneManager.h"

yh::Application::Application() : mHwnd(NULL), 
mHdc(NULL), 
mWidth(0), 
mHeight(0), 
mBackBuffer(NULL), 
mBackHdc(NULL),
mScene(nullptr)
{
	
}

yh::Application::~Application()
{
}

void yh::Application::Initialize(HWND hwnd)
{
	mHwnd = hwnd;
	mHdc = GetDC(mHwnd);

	mWidth = 512;
	mHeight = 448;

	RECT rect = { 0,0, mWidth, mHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(mHwnd,
		nullptr, 0, 0
		, rect.right - rect.left
		, rect.bottom - rect.top,
		0);
	ShowWindow(mHwnd, true);

	//윈도우 해상도와 동일한 비트맵 생성
	mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);

	//새로 생성한 비트맵을 가리키는 DC
	mBackHdc = CreateCompatibleDC(mHdc);

	HBITMAP defaultBitmap
		= (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
	DeleteObject(defaultBitmap);

	Time::Initialize();
	Input::Initialize();

	 
	SceneManager::Initialize();

	
}

void yh::Application::Run()
{
	Update();
	Render();
}

void yh::Application::Update()
{
	Time::Update();
	Input::Update();

	SceneManager::Update();
}

void yh::Application::Render()
{
	Rectangle(mBackHdc, -1, -1, mWidth + 1, mHeight + 1);
	Time::Render(mBackHdc);

	SceneManager::Render(mBackHdc);

	BitBlt(mHdc, 0, 0, mWidth, mHeight,
		mBackHdc, 0, 0, SRCCOPY);
}
