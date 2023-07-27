#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>

#include "framework.h"
#include "yhMath.h"


#pragma comment(lib, "Msimg32.lib")

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

namespace yh::enums
{
	enum class eLayerType
	{
		Background,
		Obstacle,
		PitFall,
		Player,
		Tile,
		Sword,
		Shield,
		Monster,
		Effect,
		UI,
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