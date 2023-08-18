#include "yhAsciiRender.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"
#include "yhObject.h"
#include "yhGameObject.h"

namespace yh
{
	AsciiRender::AsciiRender(): 
		sentence("")
		, RenderPosition(Vector2(170.0f, 30.0f))
		, font_scale(Vector2(2.0f, 2.0f))
		, tr(nullptr)
		, sr(nullptr)
		, image(nullptr)
		, ascii_set({})
	{
		std::wstring ui_path = UI_PATH;
		tr = GetComponent<Transform>();
		tr->SetPosition(Vector2(0.0f, 0.0f));
		sr = AddComponent<SpriteRenderer>();
		image = Resources::Load<Texture>(L"TalkingTemplate", ui_path + L"Talking\\TalkTemplate.bmp");
		sr->SetImage(image);
		sr->SetScale(Vector2(1.1f, 1.3f));
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
		std::wstring ui_path = UI_PATH;
		Vector2 container_pos = tr->GetPosition();
		RenderPosition = container_pos - RenderPosition;
		Vector2 Distance(15.0f, 30.0f);
		int vert_idx = 0;
		int hori_idx = 0;
		if (sentence == "")
			return;
		for(char ch : sentence)
		{
			if (ch == ' ')
			{
				hori_idx++;
				continue;
			}
			if (ch == '\n')
			{
				vert_idx++;
				hori_idx = 0;
				continue;
			}
			int ch_num = (int)ch;
			Texture* ascii_image = Resources::Load<Texture>((wchar_t)ch + L"ascii", ui_path + L"Letters\\" + std::to_wstring(ch_num) + L".bmp");
			Ascii* letter = object::Instantiate<Ascii>(eLayerType::Asciis, Vector2(RenderPosition.x + (Distance.x * hori_idx), RenderPosition.y + (Distance.y * vert_idx)));
			SpriteRenderer* letter_sr = letter->AddComponent<SpriteRenderer>();
			letter_sr->SetImage(ascii_image);
			letter_sr->SetScale(font_scale);
			hori_idx++;
			ascii_set.push_back(letter);
		}
	}

	void AsciiRender::Destroy()
	{
		SetState(GameObject::eState::Pause);
		for (Ascii* letter : ascii_set)
		{
			letter->SetState(GameObject::eState::Pause);
		}
	}

	void AsciiRender::Activate()
	{
		SetState(GameObject::eState::Active);
		for (Ascii* letter : ascii_set)
		{
			letter->SetState(GameObject::eState::Active);
		}
	}


	void AsciiRender::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}


	void AsciiRender::Ascii::Initialize()
	{
	}

	void AsciiRender::Ascii::Update()
	{	
		GameObject::Update();
	}

	void AsciiRender::Ascii::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}