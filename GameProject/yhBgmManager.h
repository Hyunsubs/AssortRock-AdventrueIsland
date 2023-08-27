#pragma once
#include "yhSound.h"

namespace yh
{
	enum class BgmTypes
	{
		Main,
		Castle,
		Boss,
		Ending
	};

	class BgmManager
	{
	public:
		static void PlayIndexSound(BgmTypes bgm,bool loop);
		static void StopIndexSound();
		static void Init();

	private:
		static vector<Sound*> sound_manager;

	};
}


