#pragma once
#include "CommonInclude.h"
#include "yhScene.h"

namespace yh
{
	using namespace math;
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }

	private:
		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;

		HDC mBackHdc;
		HBITMAP mBackBuffer;

		Scene* mScene;

	};
}


