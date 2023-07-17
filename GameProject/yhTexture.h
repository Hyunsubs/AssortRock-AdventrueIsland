#pragma once
#include "yhResource.h"

namespace yh
{
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
		
		void SetWidth(UINT width) { mWidth = width; }
		UINT GetWidth() { return mWidth; }
		void SetHeight(UINT height) { mHeight = height; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
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

	};
}


