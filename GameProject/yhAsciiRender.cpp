#include "yhAsciiRender.h"
#include "yhTransform.h"

namespace yh
{
	AsciiRender::AsciiRender(): 
		sentence("")
		, RenderPosition(Vector2::Zero)
		, font_scale(Vector2::One)
		, change_line(0)
	{
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
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (!sentence.empty())
		{
			for (int i = 0; i < (int)(sentence.size()); i++)
			{
				int file_number = (int)(sentence[i]);
				
			}
		}
	}
	void AsciiRender::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}


}