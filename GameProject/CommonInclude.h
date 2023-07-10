#pragma once
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <string>

#include "yhMath.h"
#include "framework.h"

namespace yh::enums
{
	enum class eLayerType
	{
		Background,
		Player,
		Monster,
		Effect,
		UI,
		End,

	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		End,

	};
}