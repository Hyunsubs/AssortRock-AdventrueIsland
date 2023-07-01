#include "Time.h"



namespace key_logic
{

	//스태틱 변수는 구현부에서 초기화가 필수다.
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f; 

	//초기화
	void Time::Initialize()
	{
		//CPU 고유 진동수를 가져온다.
		QueryPerformanceFrequency(&mCpuFrequency);

		//프로그램이 시작됐을때 진동수를 가져온다.
		QueryPerformanceCounter(&mPrevFrequency);

	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);
		float differenceFrequency = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	
	bool Time::Render(HDC hdc)
	{
		
		static float timeCheck = 0.0f;
		
		timeCheck += mDeltaTime; //
		//1초마다 fps 화면에 업데이트 해주기
		//1초 측정 방법
		//루프가 실행될때마다 timeCheck 변수에 델타 타임을 더해주면
		//timeCheck가 1이 된 순간이 1초가 된것과 같기 때문에
		//if루프 조건을 timeCheck >= 1.0f로 설정한다.
		if (timeCheck >= 1.0f)
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;
			
			//swprintf_s 사용하는 이유?
			swprintf_s(szFloat, 50, L"fps : %f", fps);
			int strLen = wcsnlen_s(szFloat, 50);

			//받아온 hdc로 화면에 텍스트 출력
			TextOut(hdc, 10, 10, szFloat, strLen);

			timeCheck = 0.0f;
			return true;
		}
		return false;

	}

}


