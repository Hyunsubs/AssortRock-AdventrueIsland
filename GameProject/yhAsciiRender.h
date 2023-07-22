#pragma once
#include "yhGameObject.h"

namespace yh
{
	using namespace math;
	class AsciiRender : public GameObject
	{
	public:
		AsciiRender();
		virtual ~AsciiRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetString(std::string sent) { sentence = sent; }
		void SetScreen(Vector2 pos) { RenderPosition = pos; }

	private:
		std::string sentence;
		Vector2 RenderPosition;
		Vector2 font_scale;
		int change_line;
	};


}
