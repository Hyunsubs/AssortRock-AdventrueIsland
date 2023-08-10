#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>
#include <assert.h>
#include <fstream>
#include <iostream>

#include "framework.h"
#include "yhMath.h"


#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

#define PLAYER_PATH L"..\\Resources\\Image\\Player\\"
#define ITEMS_PATH  L"..\\Resources\\Image\\Items\\"
#define INTERACTION_PATH L"..\\Resources\\Image\\Interaction\\"
#define MAP_PATH L"..\\Resources\\Image\\Maps\\"
#define MONSTER_PATH L"..\\Resources\\Image\\Monster\\"
#define UI_PATH L"..\\Resources\\Image\\UI\\"
#define TILE_PATH L"..\\Resources\\Image\\Tiles\\"

namespace yh::enums
{
	enum class eLayerType
	{
		PixelCollider,
		ForeBackground,
		Background,
		MapChanger,
		Stair,
		Obstacle,
		PitFall,
		Wall,
		Items,
		Player,
		Tile,
		Sword,
		Shield,
		Monster,
		Effect,
		UI,
		End,

	};

	enum class Directions
	{
		Forward,
		UpRight,
		UpLeft,
		Backward,
		DownRight,
		DownLeft,
		Left,
		Right,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		Rigidbody,
		End,

	};
}