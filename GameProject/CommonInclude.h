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

namespace yh::enums
{
	enum class eLayerType
	{
		Background,
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
		Backward,
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