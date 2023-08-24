#pragma once
#include "yhGameObject.h"

namespace yh
{
	enum class ChickenState
	{
		Moving,
		Attacked,
		Angry,
		Flying
	};


	class Chicken : public GameObject
	{
	public:
		Chicken();
		virtual ~Chicken();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void Moving();
		void Attack();
		void Angry();
		void Flying();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayerPos(Vector2 input) { player_pos = input; }
		void SetChickenState(ChickenState input) { state = input; }
		void CheckPixel(class Texture* pixel_texture, Vector2 map_size);


		class Texture* PixelTexture;
		Vector2 map_size;

	private:
		class Animator* anim;
		class Transform* tr;
		class Collider* col;


		ChickenState state;
		Vector2 player_pos;

		Directions direct;

		Vector2 make_pos_arr[12];

		int hit_count;
		int move_count;

		int rand_num;

		float move_time;
	};
}


