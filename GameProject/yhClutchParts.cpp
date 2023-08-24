#include "yhClutchParts.h"
#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhMonsterTemplate.h"
#include "yhGreenKnight.h"
#include "yhCollider.h"
#include "yhArrghus.h"
#include "yhArrghusPiece.h"


namespace yh
{
	ClutchParts::ClutchParts() :
		  image(nullptr)
		, tr(nullptr)
		, sr(nullptr)
		, direction(Directions::End)
		, col(nullptr)
		, is_captured(false)
		, is_activated(false)
	{
		tr = GetComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		col = AddComponent<Collider>();
	}


	ClutchParts::~ClutchParts()
	{
	}


	void ClutchParts::Initialize()
	{
	}


	void ClutchParts::Update()
	{
		GameObject::Update();

		wstring clutch_direction = L"";
		wstring clutch_type = L"";

		switch (direction)
		{
		case yh::enums::Directions::Forward:
			clutch_direction = L"Forward";
			break;
		case yh::enums::Directions::Backward:
			clutch_direction = L"Backward";
			break;
		case yh::enums::Directions::Left:
			clutch_direction = L"Left";
			break;
		case yh::enums::Directions::Right:
			clutch_direction = L"Right";
			break;
		default:
			break;
		}

		switch (type)
		{
		case yh::ClutchTypes::Start:
			clutch_type = L"_start.bmp";
			break;
		case yh::ClutchTypes::Middle:
			clutch_type = L"_middle.bmp";
			break;
		case yh::ClutchTypes::End:
			clutch_type = L"_end.bmp";
			col->SetSize(Vector2(20.0f,20.0f));
			break;
		default:
			break;
		}

		wstring path = L"..\\Resources\\Image\\Items_Playing\\Clutch\\";
		image = Resources::Load<Texture>(clutch_direction + clutch_type, path + clutch_direction + L"\\" + L"clutch_" + clutch_direction + clutch_type);
		sr->SetImage(image);
		sr->SetScale(Vector2::Double);


		
	}

	void ClutchParts::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void ClutchParts::OnCollisionEnter(Collider* other)
	{
		
		ArrghusPiece* piece = dynamic_cast<ArrghusPiece*>(other->GetOwner());
		if (piece != nullptr && type == ClutchTypes::End && is_activated && piece->GetPieceState() != PieceState::Dead)
		{
			Transform* clutch_tr = GetComponent<Transform>();
			Transform* monster_tr = piece->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}

		Arrghus* arrghus = dynamic_cast<Arrghus*>(other->GetOwner());
		if (arrghus != nullptr)
		{
			return;
		}
		GreenKnight* gn = dynamic_cast<GreenKnight*>(other->GetOwner());
		if (type == ClutchTypes::End && gn != nullptr && is_activated)
		{
			Transform* clutch_tr = GetComponent<Transform>();
			Transform* monster_tr = gn->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}

		MonsterTemplate* monster = dynamic_cast<MonsterTemplate*>(other->GetOwner());
		if (type == ClutchTypes::End && monster != nullptr && is_activated)
		{
			monster->SetClutch(true);
			Transform* clutch_tr = GetComponent<Transform>();
			Transform* monster_tr = monster->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}

		
	}
	void ClutchParts::OnCollisionStay(Collider* other)
	{
		ArrghusPiece* piece = dynamic_cast<ArrghusPiece*>(other->GetOwner());
		if (piece != nullptr && type == ClutchTypes::End && is_activated && piece->GetPieceState() != PieceState::Dead)
		{
			Transform* clutch_tr = GetComponent<Transform>();
			Transform* monster_tr = piece->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}

		Arrghus* arrghus = dynamic_cast<Arrghus*>(other->GetOwner());
		if (arrghus != nullptr)
		{
			return;
		}
		MonsterTemplate* monster = dynamic_cast<MonsterTemplate*>(other->GetOwner());
		if (type == ClutchTypes::End && monster != nullptr && is_activated && monster->GetMonsterState() != MonsterState::Death)
		{
			monster->SetClutch(true);
			Transform* clutch_tr = GetComponent<Transform>();
			Transform* monster_tr = monster->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}
		GreenKnight* gn = dynamic_cast<GreenKnight*>(other->GetOwner());
		if (type == ClutchTypes::End && gn != nullptr && is_activated && gn->GetMonsterState() != MonsterState::Death)
		{
			Transform* clutch_tr = GetComponent<Transform>();
			Transform* monster_tr = gn->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}
	}
	void ClutchParts::OnCollisionExit(Collider* other)
	{
		
	}
}