#pragma once
#include "yhEntity.h"
#include "yhLayer.h"

namespace yh
{
	using namespace yh::enums;


	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		
		void AddGameObject(eLayerType type, GameObject* gameObj)
		{
			mLayers[(int)type].AddGameObject(gameObj);
		}

		void SetLoaded(bool input) { is_loaded = input; }
		bool GetLoaded() { return is_loaded; }


		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }

	private:
		std::vector<Layer> mLayers;
		bool is_loaded;
	};
}


