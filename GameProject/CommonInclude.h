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
#define PLAYING_ITEMS_PATH  L"..\\Resources\\Image\\Items_Playing\\"
#define INTERACTION_PATH L"..\\Resources\\Image\\Interaction\\"
#define MAP_PATH L"..\\Resources\\Image\\Maps\\"
#define MONSTER_PATH L"..\\Resources\\Image\\Monster\\"
#define UI_PATH L"..\\Resources\\Image\\UI\\"
#define TILE_PATH L"..\\Resources\\Image\\Tiles\\"
#define NPC_PATH L"..\\Resources\\Image\\NPC\\"
#define BOSS_PATH L"..\\Resources\\Image\\Boss\\"
using namespace std;

namespace yh::enums
{
	enum class eLayerType
	{
		PixelCollider,
		ForeBackground,
		Background,
		MapChanger,
		Asciis,
		Stair,
		Step,
		Grass,
		Obstacle,
		PitFall,
		NPC,
		Wall,
		Items,
		Player,
		Tile,
		Sword,
		Projectile,
		Clutch,
		Shield,
		Monster,
		Boss,
		Effect,
		UI,
		End,

	};

	enum class MonsterState
	{
		Idle,
		Move,
		MoveReady,
		Attack,
		KnockBack,
		Death,
		Falling,
		Chasing,
		Freeze,
		Ui,
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