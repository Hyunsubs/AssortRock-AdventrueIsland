#include "yhTexture.h"
#include "yhApplication.h"

extern yh::Application appllication;

namespace yh
{
	Texture::Texture()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mImage(nullptr)
		, mType(eTextureType::None)
	{

	}
	Texture::~Texture()
	{
		delete mImage;
		mImage = nullptr;

		DeleteObject(mBitmap);
		mBitmap = NULL;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		//확장자 bmp일때와 png일때

		std::wstring ext = path.substr(path.find_last_of(L".") + 1);


		if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0,
				LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return S_FALSE;

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = appllication.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP defaultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(defaultBitmap);
		}

		else if (ext == L"png")
		{
			mType = eTextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());
			
			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();

		}
		

		return S_OK;

	}


}
