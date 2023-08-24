#include "yhArrghusShadow.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"

namespace yh
{
	ArrghusShadow::ArrghusShadow() :
		  image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		wstring boss_path = BOSS_PATH;
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		image = Resources::Load<Texture>(L"ArrghusShadowImage", boss_path + L"Arrghus\\SecondPhase\\shadow\\arrghus_shadow_01.bmp");
		sr->SetImage(image);
		sr->SetScale(Vector2::Double);
	}
	ArrghusShadow::~ArrghusShadow()
	{
	}
	void ArrghusShadow::Initialize()
	{
	}
	void ArrghusShadow::Update()
	{
		GameObject::Update();
	}
	void ArrghusShadow::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
