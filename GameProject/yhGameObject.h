#pragma once
#include "yhEntity.h"
#include "yhComponent.h"

namespace yh
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Pause,
			Dead,
			End,
		};

		friend static __forceinline void Destroy(GameObject* gameObject);

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


		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		eState GetState() { return mState; }
		void SetState(eState input) { mState = input; }
		void Pause() { mState = eState::Pause; }
		
	private:
		std::vector<Component*> mComponents;
		eState mState;

		void death() { mState = eState::Dead; }
	};
		static __forceinline void Destroy(GameObject* gameObject)
		{
			gameObject->death();
		}
	
}


