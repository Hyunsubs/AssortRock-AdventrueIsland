#pragma once
#include "yhResource.h"

namespace yh
{
	using namespace math;
	class Texture;
	class Animator;

	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			Vector2 scale;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
				, scale(Vector2::One)
			{

			}
		};

		Animation();
		~Animation();

		void Update();
		void Render(HDC hdc);
		
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }

		void Create(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration);

		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

	private:
		Animator* mAnimator;
		Texture* mTexture;
		
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}


