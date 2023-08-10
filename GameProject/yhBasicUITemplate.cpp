#include "yhBasicUITemplate.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhCollider.h"
#include "yhTexture.h"
#include "yhResources.h"


namespace yh
{
	BasicUITemplate::BasicUITemplate() :
		  image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
		, col(nullptr)
	{
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		col = AddComponent<Collider>();
		image = nullptr;

	}

	BasicUITemplate::BasicUITemplate(std::wstring name, std::wstring path) :
		  image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
		, col(nullptr)
	{
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		col = AddComponent<Collider>();
		image = Resources::Load<Texture>(name, path);
		sr->SetImage(image);
	}


	BasicUITemplate::~BasicUITemplate()
	{
	}
	void BasicUITemplate::Initialize()
	{
	}
	void BasicUITemplate::Update()
	{
		GameObject::Update();
	}
	void BasicUITemplate::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BasicUITemplate::OnCollisionEnter(Collider* other)
	{
	}
	void BasicUITemplate::OnCollisionStay(Collider* other)
	{
	}
	void BasicUITemplate::OnCollisionExit(Collider* other)
	{
	}


}