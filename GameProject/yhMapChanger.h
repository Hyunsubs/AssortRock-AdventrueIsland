#pragma once
#include "yhGameObject.h"

namespace yh
{
	using namespace math;
	class MapChanger : public GameObject
	{
	public:
		MapChanger();
		virtual ~MapChanger() override;


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetColliderSize(Vector2 size);
		void SetSceneName(std::wstring name);
		void SetLoadPos(Vector2 pos) { load_pos = pos; }
		void SaveLoadPos(Vector2 pos);

	private:
		std::wstring scene_name;
		Vector2 load_pos;

		class Transform* tr;
		class Collider* col;

	};
}