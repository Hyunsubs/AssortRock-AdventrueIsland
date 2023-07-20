#include "yhAnimation.h"
#include "yhTime.h"
#include "yhAnimator.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhGameObject.h"
#include "yhCamera.h"


yh::Animation::Animation()
	: mAnimator(nullptr)
	, mTexture(nullptr)
	, mSpriteSheet{}
	, mIndex(-1)
	, mTime(0.0f)
	, mbComplete(false)
{
}

yh::Animation::~Animation()
{
}

void yh::Animation::Update()
{
	if (mbComplete)
		return;
	
	mTime += Time::DeltaTime();
	if (mSpriteSheet[mIndex].duration < mTime)
	{
		mTime = 0.0f;
		if (mIndex < mSpriteSheet.size() - 1)
			mIndex++;
		else
			mbComplete = true;
	}

}

void yh::Animation::Render(HDC hdc)
{
	if (mTexture == nullptr)
		return;

	Sprite sprite = mSpriteSheet[mIndex];
	Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();

	Animator* animator = mAnimator;

	mTexture->Render(hdc
		, pos
		, sprite.size
		, sprite.leftTop
		, sprite.size
		, sprite.offset
		, animator->GetScale()
		, animator->GetAlpha()
		, tr->GetRotation());

}

void yh::Animation::Create(const std::wstring& name, 
	Texture* texture, 
	Vector2 leftTop, 
	Vector2 size, 
	Vector2 offset,
	UINT spriteLength, 
	float duration)
{
	mTexture = texture;
	
	for (size_t i = 0; i < spriteLength; i++)
	{
		Sprite sprite = {};

		sprite.leftTop.x = leftTop.x + (size.x * i);
		sprite.leftTop.y = leftTop.y;
		if (sprite.leftTop.x >= texture->GetWidth())
		{
			sprite.leftTop.x = sprite.leftTop.x - texture->GetWidth();
			sprite.leftTop.y = leftTop.y + size.y;
		}
		sprite.size = size;
		sprite.offset = offset;
		sprite.duration = duration;

		mSpriteSheet.push_back(sprite);

	}
}

void yh::Animation::Reset()
{
	mTime = 0.0f;
	mIndex = 0;
	mbComplete = false;
}
