#pragma once
#include "yhResource.h"

namespace yh
{
	using namespace math;
	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};


	class Texture : public Resource
	{

	public:
		Texture();
		virtual ~Texture();

		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;

		void Render(HDC hdc
			, Vector2 pos
			, Vector2 size
			, Vector2 leftTop
			, Vector2 rightBottom
			, Vector2 offset = Vector2::Zero
			, Vector2 scale = Vector2::One
			, float alpha = 1.0f
			, float rotate = 0.0f);
		
		COLORREF GetTexturePixel(int x, int y);

		void SetWidth(UINT width) { mWidth = width; }
		UINT GetWidth() { return mWidth; }
		void SetHeight(UINT height) { mHeight = height; }
		UINT GetHeight() { return mHeight; }

		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		void SetType(eTextureType type) { mType = type; }
		Gdiplus::Image* GetImage() { return mImage; }
		void SetHBitmap(HBITMAP bitmap) { mBitmap = bitmap; }
		void SetHdc(HDC hdc) { mHdc = hdc; }


	private:
		eTextureType mType;
		Gdiplus::Image* mImage;

		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
		bool mbAffectCamera;

	};
}


