#include "yhToolScene.h"
#include "yhHouse.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhObject.h"
#include "yhInput.h"
#include "yhTexture.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhBackGround.h"
#include "yhCamera.h"
#include "yhTile.h"

namespace yh
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{

		Texture* springFloor
			= Resources::Load<Texture>(L"SprintFloorTile", L"..\\Resources\\Image\\Tiles\\House_Interior.bmp");

	}
	void ToolScene::Update()
	{

		if (Input::GetKeyDown(eKeyCode::MouseLeft) && GetFocus())
		{
			Vector2 mousePos = Input::GetMousePosition();

			int idxX = mousePos.x / (TILE_WIDTH * 3);
			int idxY = mousePos.y / (TILE_HEIGHT * 3);

			Vector2 offset = Vector2((TILE_WIDTH * 3) / 2.0f, (TILE_HEIGHT * 3) / 2.0f);
			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile
				, Vector2(idxX * (TILE_WIDTH * 3) + offset.x
					, idxY * (TILE_HEIGHT * 3) + offset.y));

			tile->SetTile(Tile::mSelectedX, Tile::mSelectedY);
		}
	}
	void ToolScene::Render(HDC hdc)
	{

		Scene::Render(hdc);

		int maxRow = 512 / (TILE_HEIGHT * 3) + 1;
		for (size_t y = 0; y < maxRow; y++)
		{
			MoveToEx(hdc, 0, TILE_HEIGHT * y * 3, NULL);      //      라인(선) 시작
			LineTo(hdc, 1280, TILE_HEIGHT * y * 3);        //          라인(선) 끝
		}

		int maxColumn = 512 / (TILE_WIDTH * 3) + 1;
		for (size_t x = 0; x < maxColumn; x++)
		{
			MoveToEx(hdc, TILE_WIDTH * x * 3, 0, NULL);      //      라인(선) 시작
			LineTo(hdc, TILE_WIDTH * x * 3, 720);        //          라인(선) 끝
		}
	}
}