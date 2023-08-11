#pragma once
#include "yhBasicUITemplate.h"


namespace yh
{
	using namespace math;
	class AsciiRender : public GameObject
	{
	public:
		class Ascii : public GameObject
		{
		public:
			virtual void Initialize() override;
			virtual void Update() override;
			virtual void Render(HDC hdc) override;
		};

		AsciiRender();
		virtual ~AsciiRender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetString(std::string sent) { sentence = sent; }
		void SetScreen(Vector2 pos) { RenderPosition = pos; }
		void SetFontSize(Vector2 size) { font_scale = size; }

		void PrintAsciis();
		void Destroy();
		void Activate();

	private:
		std::string sentence;
		Vector2 RenderPosition;
		Vector2 font_scale;
		std::vector<class Ascii*> ascii_set;

		class Texture* image;
		class SpriteRenderer* sr;
		class Transform* tr;
		
	};


}
