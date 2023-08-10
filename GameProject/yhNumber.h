#pragma once
#include "yhGameObject.h"


namespace yh
{
	class Number : public GameObject
	{
	public:

		Number();
		virtual ~Number() override;


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;



		int GetNumber() { return cur_number; }
		void SetNumber(int input) { cur_number = input; }



	private:
		int cur_number;
		std::wstring number_string;
		std::wstring ui_path;
		class SpriteRenderer* sr;
		class Transform* tr;
		class Texture* image;
	};
}


