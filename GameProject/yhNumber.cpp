#include "yhNumber.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhTexture.h"
#include "yhResources.h"

namespace yh
{
	Number::Number() :
		  sr(nullptr)
		, tr(nullptr)
		, image(nullptr)
		, cur_number(0)
		, ui_path(UI_PATH)
	{
		number_string = std::to_wstring(cur_number);
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		image = Resources::Load<Texture>(L"Number"+ number_string, ui_path + L"Number\\number" + number_string + L".bmp");
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f,2.0f));
	}

	Number::~Number()
	{

	}

	void Number::Initialize()
	{
		
	}

	void Number::Update()
	{
		GameObject::Update();
		number_string = std::to_wstring(cur_number);
		image = Resources::Load<Texture>(L"Number" + number_string, ui_path + L"Number\\number" + number_string + L".bmp");
		sr->SetImage(image);
	}

	void Number::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}