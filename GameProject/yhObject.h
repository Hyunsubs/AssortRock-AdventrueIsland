#pragma once
#include "yhScene.h"
#include "yhGameObject.h"
#include "yhSceneManager.h"

namespace yh::object
{
	template <typename T>
	static __forceinline T* Instantiate(eLayerType type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(type, gameObject);

		return gameObject;
	}


}