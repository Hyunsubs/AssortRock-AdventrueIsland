#include "yhBgmManager.h"
#include "yhResources.h"
#include "CommonInclude.h"

namespace yh
{
	vector<Sound*> BgmManager::sound_manager = {};

	void yh::BgmManager::Init()
	{
		Sound* main_theme = Resources::Load<Sound>(L"MainThemeSound", L"..\\Resources\\sound\\main_theme.wav");
		Sound* castle_theme = Resources::Load<Sound>(L"CastleThemeSound", L"..\\Resources\\sound\\inside_castle.wav");
		Sound* boss_theme = Resources::Load<Sound>(L"BossThemeSound", L"..\\Resources\\sound\\boss_bgm.wav");
		Sound* ending_theme = Resources::Load<Sound>(L"EndingSound", L"..\\Resources\\sound\\Ending.wav");
		sound_manager.push_back(main_theme);
		sound_manager.push_back(castle_theme);
		sound_manager.push_back(boss_theme);
		sound_manager.push_back(ending_theme);
	}


	void yh::BgmManager::PlayIndexSound(BgmTypes bgm, bool loop)
	{
		for (int i = 0; i < sound_manager.size(); i++)
		{
			sound_manager[i]->Stop(true);
		}

		sound_manager[(int)bgm]->Play(loop);

	}

	void yh::BgmManager::StopIndexSound()
	{
		for (int i = 0; i < sound_manager.size(); i++)
		{
			sound_manager[i]->Stop(true);
		}
	}

}