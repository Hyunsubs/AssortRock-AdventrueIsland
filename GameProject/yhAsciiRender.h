#pragma once
#include "yhBasicUITemplate.h"


namespace yh
{
	using namespace math;
	class AsciiRender : public BasicUITemplate
	{
	public:
		AsciiRender();
		virtual ~AsciiRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetString(std::string sent) { sentence = sent; }
		void SetScreen(Vector2 pos) { RenderPosition = pos; }
		void SetFontSize(Vector2 size) { font_scale = size; }

		void PrintAsciis();

	private:
		std::string sentence;
		Vector2 RenderPosition;
		Vector2 font_scale;
		std::vector<class SpriteRenderer> string_set;

		class Texture* image;
		class SpriteRenderer* sr;
		class Transform* tr;
		
	};


}
