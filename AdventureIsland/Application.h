#pragma once
#include "CommonInclude.h"
#include "math_thing.h"

namespace key_logic
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

	private:
		HWND mHwnd;
		HDC mHdc;

		Vector2 mPlayerPos;

	};
}



