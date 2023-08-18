#pragma once
#include "yhPlayerTemplate.h"


namespace yh
{

	class House : public PlayerTemplate
	{
	public:
		House();
		virtual ~House();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class MapChanger* nearhouse_map_changer;
		class MapChanger* castle_map_changer;
		class AsciiRender* asciirender;
		class Arrghus* boss;
	};
}


