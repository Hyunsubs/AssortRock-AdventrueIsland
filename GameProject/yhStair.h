#pragma once
#include "yhGameObject.h"
//¿Ã¶ó°¥¶© -110 ³»·Á°¥¶© +110


namespace yh
{
	class Stair : public GameObject
	{
	public:
		Stair();
		virtual ~Stair() override;


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetColSize(Vector2 input);

	private:
		class Transform* tr;
		class Collider* col;
		class Sound* up_sound;
		class Sound* down_sound;
		bool sound_played;
	};
}




