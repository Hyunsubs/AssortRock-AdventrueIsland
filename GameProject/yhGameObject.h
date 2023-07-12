#pragma once
#include "yhEntity.h"
#include "yhComponent.h"

namespace yh
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		template <typename T>
		T* GetComponent()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				//자식 타입과 T타입이 일치하다면
				//주소를 반환 아니면 nullptr 반환

				comp = dynamic_cast<T*>(c);
				if (comp != nullptr)
					return comp;

			}
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			mComponents.push_back(comp);
			comp->SetOwner(this);

			return comp;
		}

	private:
		std::vector<Component*> mComponents;
	};
}


