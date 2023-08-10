#include "yhAsciiRender.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"


namespace yh
{
	AsciiRender::AsciiRender(): 
		sentence("")
		, RenderPosition(Vector2::Zero)
		, font_scale(Vector2::One)
		, tr(nullptr)
		, sr(nullptr)
		, image(nullptr)
	{
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		image = Resources::Load<Texture>(L"", L"");
	}
	AsciiRender::~AsciiRender()
	{
	}

	void AsciiRender::Initialize()
	{

	}


	void AsciiRender::Update()
	{
		GameObject::Update();
	}

	void AsciiRender::PrintAsciis()
	{
		
	}


	void AsciiRender::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}


}