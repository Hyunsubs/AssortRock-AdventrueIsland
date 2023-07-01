#pragma once
#include "CommonInclude.h"

//union 자료형
//유니온은 안에 구현된 자료들의 메모리를 서로 공유하게 만들어준다.




//delta time이란
//델타는 보통 차이를 뜻한다
//델타 타임 기법은 걸린 시간을 측정하여 동일한 루프 횟수를 구현할수 있는 방식이다.

//CPU는 정확한 시간을 잴수는 없지만
//CPU 고유의 진폭을 활용하여 일정한 시간을 구할 수 있다.



//CPU의 고유 진폭수를 구하는 함수
//QueryPerformanceFrequency() 인자로 주소를 받아옴


//프로그램이 시작됐을때 진폭수를 가져오는 함수
//QueryPerformanceCounter()
namespace key_logic
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		__forceinline static float DelataTime() { return mDeltaTime; }

	
		//LARGE_INTERGER는 16바이트 짜리 데이터를 구조체로 구현한것이다.4
		//Low Part High Part로 나뉘어져 있고
		//한번에 불러올땐 QuadPart로 불러온다.

		//static casting
		//static_cast<자료형>
		//c++ 스타일 형변환 보다 더 안전하다.


		//델타 타임 구하기 공식 
		//이전 진동수와 현재 진폭 차이를 CPU 고유 진폭수로 나눈다.
		//

	private:
		static LARGE_INTEGER mCpuFrequency; 
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
	};
}


