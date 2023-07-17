#pragma once
#include "yhComponent.h"
#include "yhAnimation.h"

namespace yh
{
	using namespace math;
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop, Vector2 size, UINT spriteLength
			, Vector2 offset = Vector2::Zero, float duration = 0.1f,
			Vector2 scale = Vector2::One);
		void CreateAnimationFolder(const std::wstring& name
			, const std::wstring& path
			, Vector2 offset = Vector2::Zero, float duration = 0.1f);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = false);

		bool GetAffectedCamera() { return mbAffectedCamera; }
		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }


	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		bool mbLoop;
		bool mbAffectedCamera;
		float mAlpha;
	};
}


