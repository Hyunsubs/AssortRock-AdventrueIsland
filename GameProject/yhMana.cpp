#include "yhMana.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhCamera.h"

namespace yh
{
	Mana::Mana() : mp(0)
	{
		tr = GetComponent<Transform>();
		image = Resources::Load<Texture>(L"ManaContainer", L"..\\Resources\\Image\\UI\\mana\\mana" + std::to_wstring(mp) + L".bmp");
		sr = AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
	}

	Mana::~Mana()
	{
	}

	void Mana::Initialize()
	{
		
	}

	void Mana::Update()
	{
		GameObject::Update();
		if (mp <= 0)
			mp = 0;
		image = Resources::Load<Texture>(L"ManaContainer"+std::to_wstring(mp), L"..\\Resources\\Image\\UI\\mana\\mana" + std::to_wstring(mp) + L".bmp");
		sr->SetImage(image);
	}

	void Mana::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}

